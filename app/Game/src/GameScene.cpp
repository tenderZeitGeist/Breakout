#include <Engine/Configuration.h>
#include <Engine/EventManager.h>
#include <Engine/TextureRenderer.h>
#include <Game/Game.h>
#include <Game/GameEvent.h>
#include <Game/GameScene.h>

#include <SDL2/SDL.h>

#include <algorithm>
#include <ranges>

GameScene::GameScene(std::shared_ptr<events::EventManager> eventManager, const TextureRenderer& textureRenderer)
    : m_topWall(0.f, -1.f)
    , m_leftWall(1.0, 0.f)
    , m_rightWall(-1.f, 0.f)
    , m_ball(m_paddle, eventManager)
    , m_score()
    , m_lifePoints(config::defaultLifePoints)
    , m_gameOverState(textureRenderer)
    , m_eventManager(std::move(eventManager)) {
    initializeWalls();
    initializeBricks();
    initializePaddle();
    initializeBall();
    initializeScore();
    initializeLifePoints();
    m_eventManager->subscribe<GameScene, events::BrickDestroyed, &GameScene::onBrickDestroyed>(this);
    m_eventManager->subscribe<GameScene, events::BallOutOfBounds, &GameScene::onBallOutOfBounds>(this);
    m_eventManager->subscribe<GameScene, events::IncreaseScore, &GameScene::onIncreaseScore>(this);
    m_eventManager->subscribe<GameScene, events::DestoryAllBricks, &GameScene::onDestroyAllBricks>(this);
    m_eventManager->subscribe<GameScene, events::StartMovingLeft, &GameScene::onStartMovingLeft>(this);
    m_eventManager->subscribe<GameScene, events::StopMovingLeft, &GameScene::onStopMovingLeft>(this);
    m_eventManager->subscribe<GameScene, events::StartMovingRight, &GameScene::onStartMovingRight>(this);
    m_eventManager->subscribe<GameScene, events::StopMovingRight, &GameScene::onStopMovingRight>(this);
    m_eventManager->subscribe<GameScene, events::ReturnToMenu, &GameScene::onReturnToMenu>(this);
}

void GameScene::update(float delta) {
    if (m_gameOver) {
        m_gameOverState.update(delta);
        return;
    }

    setPaddleDirection();
    for (auto& entity : m_entities) {
        entity.get().update(delta);
    }
    checkForGameOver();
}

void GameScene::render(SDL_Renderer& renderer) {
    for (auto& entity : m_entities) {
        entity.get().render(renderer);
    }

    if (!m_gameOver) {
        return;
    }

    m_gameOverState.render(renderer);
}

void GameScene::reset() {
    for (auto entityRef : m_entities) {
        entityRef.get().reset();
    }
    m_gameOver = false;
    m_gameOverState.reset();
}

void GameScene::enter() {
}

void GameScene::exit() {
}

void GameScene::onDebug(bool debug) {
    for (auto entityRef : m_entities) {
        entityRef.get().onDebug(debug);
    }
}

void GameScene::initializePaddle() {
    m_paddle.init({.x = config::windowHalfWidth - config::slotHalfWidth,
                   .y = config::windowHeight - 100,
                   .width = config::slotWidth,
                   .height = config::slotHeight,
                   .velocity = static_cast<float>(config::windowHeight) / 1200.f,
                   .color = config::kPaddleColor}

    );
    m_paddle.setWalls({m_leftWall, m_rightWall});
    m_entities.emplace_back(m_paddle);
}

void GameScene::initializeWalls() {
    m_topWall.init({.x = 0,
                    .y = 0,
                    .width = config::windowWidth,
                    .height = config::scoreHeight + config::slotHeight,
                    .color = config::kDebugColor});

    m_entities.emplace_back(m_topWall);

    m_leftWall.init({.x = 0,
                     .y = 0,
                     .width = config::slotHalfWidth,
                     .height = config::windowHeight,
                     .color = config::kDebugColor});

    m_entities.emplace_back(m_leftWall);

    m_rightWall.init({.x = config::windowWidth - config::slotHalfWidth,
                      .y = 0,
                      .width = config::slotHalfWidth,
                      .height = config::windowHeight,
                      .color = config::kDebugColor});

    m_entities.emplace_back(m_rightWall);
}

void GameScene::initializeBricks() {
    constexpr auto amountX = 14;
    constexpr auto amountY = 8;
    m_bricks.reserve(amountX * amountY);
    for (int x = 0; x < amountX; ++x) {
        for (int y = 0; y < amountY; ++y) {
            const auto colorIndex = static_cast<std::size_t>(y / 2);
            m_bricks.emplace_back();
            auto& brickRef = m_bricks.back();
            brickRef.init(
                    {.x = config::slotHalfWidth + x * (config::slotWidth + config::slotSpacing),
                     .y = config::slotHalfWidth + y * (config::slotHeight + config::slotSpacing) + config::scoreHeight,
                     .width = config::slotWidth,
                     .height = config::slotHeight,
                     .color = config::kBricksFillStyles[colorIndex]});
            brickRef.setValue(7 - static_cast<int>(colorIndex * 2));
            m_entities.emplace_back(brickRef);
        }
    }
}

void GameScene::initializeBall() {
    m_ball.init({.x = config::windowHalfWidth - config::slotHalfHeight,
                 .y = config::windowHalfHeight - config::slotHalfHeight,
                 .width = config::slotHalfHeight ,
                 .height = config::slotHalfHeight,
                 .color = config::kPaddleColor,
                 .shape = ShapeType::CIRCLE});

    m_ball.setWalls({m_topWall, m_leftWall, m_rightWall});
    std::vector<std::reference_wrapper<Brick>> brickRefs;
    brickRefs.reserve(m_bricks.size());
    for (std::reference_wrapper<Brick> brick : m_bricks) {
        brickRefs.push_back(brick);
    }
    m_ball.setBricks(std::move(brickRefs));
    m_entities.emplace_back(m_ball);
}

void GameScene::initializeScore() {
    constexpr auto x = config::windowWidth - config::scoreWidth - config::slotHalfWidth - config::scoreSpacing * 2;
    constexpr auto y = config::slotHalfHeight;
    m_score.init(
            {.x = x, .y = y, .width = config::scoreWidth, .height = config::scoreHeight, .color = config::kWhiteColor});
    m_entities.emplace_back(std::ref(m_score));
}

void GameScene::initializeLifePoints() {
    constexpr auto x = config::slotHalfWidth;
    constexpr auto y = config::slotHalfHeight;
    m_lifePoints.init({.x = x,
                       .y = y,
                       .width = static_cast<int>(config::slotWidth * 1.25),
                       .height = config::scoreHeight,
                       .color = config::kWhiteColor});
    m_entities.emplace_back(std::ref(m_lifePoints));
}

void GameScene::setPaddleDirection() {
    static constexpr float coefficient = 1.f;
    const float leftDirection = static_cast<float>(m_moveLeft) * -coefficient;
    const float rightDirection = static_cast<float>(m_moveRight) * coefficient;
    m_paddle.getMoveable().get().setDirectionX(leftDirection + rightDirection);
}

void GameScene::setGameOverState() {
    m_gameOver = true;
    m_ball.getDrawable().get().setVisible(false);
    m_paddle.getDrawable().get().setVisible(false);
    m_gameOverState.setActiveText(m_lifePoints.getLifePoints() > 0 ? GameOverText::WINNING : GameOverText::LOSING);
}

void GameScene::checkForGameOver() {
    const auto hitAllBricks = std::ranges::all_of(m_bricks, [](auto& brick) {
        return !brick.getDrawable().get().isVisible() && !brick.getCollidable().get().isEnabled();
    });
    if (!hitAllBricks) {
        return;
    }
    setGameOverState();
}

void GameScene::onBrickDestroyed(events::BrickDestroyed& e) {
    auto& brick = e.brick.get();
    brick.getDrawable().get().setVisible(false);
    brick.getCollidable().get().setEnabled(false);
    m_score.increaseScore(brick.getValue());
    m_score.setBlinking(true);
    checkForGameOver();
}

void GameScene::onBallOutOfBounds(events::BallOutOfBounds&) {
    m_ball.reset();
    m_paddle.reset();

    const auto currentLifePoints = m_lifePoints.getLifePoints() - 1;
    m_lifePoints.setLifePoints(currentLifePoints);
    if (currentLifePoints <= 0) {
        setGameOverState();
        return;
    }

    m_eventManager->notify(events::StartStop());
}

void GameScene::onIncreaseScore(events::IncreaseScore& e) {
    m_score.increaseScore(e.m_value);
    m_score.setBlinking(true);
}

void GameScene::onDestroyAllBricks(events::DestoryAllBricks&) {
    for (auto& brick : m_bricks) {
        m_eventManager->notify(events::BrickDestroyed(std::ref(brick)));
    }
}

void GameScene::onStartMovingLeft(events::StartMovingLeft&) {
    m_moveLeft = true;
}

void GameScene::onStopMovingLeft(events::StopMovingLeft&) {
    m_moveLeft = false;
}

void GameScene::onStartMovingRight(events::StartMovingRight&) {
    m_moveRight = true;
}

void GameScene::onStopMovingRight(events::StopMovingRight&) {
    m_moveRight = false;
}

void GameScene::onReturnToMenu(events::ReturnToMenu&) {
    if (!m_gameOver) {
        return;
    }
    m_eventManager->notify(events::GameOver());
}
