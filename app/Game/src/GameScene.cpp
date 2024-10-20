//
// Created by zeitgeist on 06.10.23.
//

#include <SDL2/SDL.h>

#include "Game/Game.h"
#include "Game/GameScene.h"
#include "Game/GameEvent.h"

#include <Engine/Configuration.h>
#include <Engine/EventManager.h>

#include <iostream>
#include <algorithm>
#include <ranges>

GameScene::GameScene(std::reference_wrapper<const KeyHandler> keyHandler, std::shared_ptr<events::EventManager> eventManager)
: m_topWall(0.f, -1.f)
, m_leftWall(1.0, 0.f)
, m_rightWall(-1.f, 0.f)
, m_ball(m_paddle, eventManager)
, m_keyHandler(keyHandler)
, m_eventManager(std::move(eventManager)){
    initializeWalls();
    initializeBricks();
    initializePaddle();
    initializeBall();
    m_eventManager->subscribe<GameScene, events::BrickDestroyedEvent, &GameScene::onBrickDestroyed>(this);
    m_eventManager->subscribe<GameScene, events::BallOutOfBoundsEvent, &GameScene::onBallOutOfBounds>(this);
}

void GameScene::update(float delta) {
    setPaddleDirection();
    for (auto& entity: m_entities) {
        entity.get().update(delta);
    }
}

void GameScene::render(SDL_Renderer& renderer) {
    for (auto& entity: m_entities) {
        entity.get().render(renderer);
    }
}

void GameScene::enter() {

}

void GameScene::exit() {
}

void GameScene::onDebug(bool debug) {
    for (auto entityRef: m_entities) {
        entityRef.get().onDebug(debug);
    }
}

void GameScene::initializePaddle() {
    m_paddle.init({
            .x = config::windowHalfWidth - config::slotHalfWidth,
            .y = config::windowHeight - 100,
            .width = config::slotWidth,
            .height = config::slotHeight,
            .velocity = static_cast<float>(config::windowHeight) / 1350.f,
            .color = config::kPaddleColor
        }

    );
    m_paddle.setWalls({m_leftWall, m_rightWall});
    m_entities.emplace_back(m_paddle);
}

void GameScene::initializeWalls() {
    m_topWall.init({
        .x = 0,
        .y = 0,
        .width = config::windowWidth,
        .height = config::slotHeight,
        .color = config::kDebugColor
    });

    m_entities.emplace_back(m_topWall);

    m_leftWall.init({
        .x = 0,
        .y = 0,
        .width = config::slotHalfWidth,
        .height = config::windowHeight,
        .color = config::kDebugColor
    });

    m_entities.emplace_back(m_leftWall);

    m_rightWall.init({
        .x = config::windowWidth - config::slotHalfWidth,
        .y = 0,
        .width = config::slotHalfWidth,
        .height = config::windowHeight,
        .color = config::kDebugColor
    });

    m_entities.emplace_back(m_rightWall);
}

void GameScene::initializeBricks() {
    constexpr auto amountX = 14;
    constexpr auto amountY = 8;
    m_bricks.reserve(amountX * amountY);
    for (int y = 0; y < amountY; ++y) {
        const auto colorIndex = y / 2;
        for (int x = 0; x < amountX; ++x) {
            m_bricks.emplace_back();
            auto& brickRef = m_bricks.back();
            brickRef.init({
                .x = config::slotHalfWidth + x * (config::slotWidth + config::slotSpacing),
                .y = config::slotHalfWidth + y * (config::slotHeight + config::slotSpacing),
                .width = config::slotWidth,
                .height = config::slotHeight,
                .color = config::kBricksFillStyles[colorIndex]
            });
            m_entities.emplace_back(brickRef);
        }
    }
}

void GameScene::initializeBall() {
    m_ball.init({
        .x = config::windowHalfWidth - config::slotHalfHeight,
        .y = config::windowHalfHeight - config::slotHalfHeight,
        .width = config::slotHeight,
        .height = config::slotHeight,
        .color = config::kPaddleColor
    });

    m_ball.setWalls({m_topWall, m_leftWall, m_rightWall});
    std::vector<std::reference_wrapper<Brick>> brickRefs;
    brickRefs.reserve(m_bricks.size());
    for (std::reference_wrapper<Brick> brick : m_bricks) {
        brickRefs.push_back(brick);
    }
    m_ball.setBricks(std::move(brickRefs));
    m_entities.emplace_back(m_ball);
}

void GameScene::setPaddleDirection() const {
    const auto& keyStates = m_keyHandler.get().getKeyStates();
    const float leftDirection = static_cast<float>(keyStates[KeyHandler::LEFT]) * -1.f;
    const float rightDirection = static_cast<float>(keyStates[KeyHandler::RIGHT]) * 1.f;
    m_paddle.getMoveable()->setDirectionX(leftDirection + rightDirection);
}

void GameScene::onBrickDestroyed(events::BrickDestroyedEvent& e) {
    auto& brick = e.brick;
    brick.getDrawable()->setVisible(false);
    brick.getCollideable()->setEnabled(false);
    m_pointerCounter += brick.getValue();
}

void GameScene::onBallOutOfBounds(events::BallOutOfBoundsEvent& e) {
    m_ball.reset();
    --m_lifeCounter;
    m_eventManager->notify(events::StartStop());
}
