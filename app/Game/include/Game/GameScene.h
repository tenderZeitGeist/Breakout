//
// Created by zeitgeist on 06.10.23.
//

#pragma once

#include "Ball.h"
#include "Brick.h"
#include "LifePoints.h"
#include "Scene.h"
#include "Score.h"
#include "Paddle.h"
#include "Wall.h"
#include "GameOverState.h"

#include <Engine/Text.h>

#include <vector>

class Entity;
class Game;

namespace events {
    class EventManager;
    struct StartMovingLeft;
    struct StopMovingLeft;
    struct StartMovingRight;
    struct StopMovingRight;
    struct BrickDestroyed;
    struct BallOutOfBounds;
    struct ReturnToMenu;
}

class GameScene
    : public Scene {
public:
    explicit GameScene(std::shared_ptr<events::EventManager> eventManager, const TextureRenderer& textureRenderer);
    ~GameScene() override = default;

    void update(float delta) override;
    void render(SDL_Renderer& renderer) override;
    void reset() override;
    void enter() override;
    void exit() override;

    void onDebug(bool debug) override;

private:
    void initializePaddle();
    void initializeWalls();
    void initializeBricks();
    void initializeBall();
    void initializeScore();
    void initializeLifePoints();
    void setPaddleDirection() const;
    void setGameOverState();
    void checkForGameOver();

    void onBrickDestroyed(events::BrickDestroyed& e);
    void onBallOutOfBounds(events::BallOutOfBounds&);
    void onIncreaseScore(events::IncreaseScore& e);
    void onDestroyAllBricks(events::DestoryAllBricks&);
    void onStartMovingLeft(events::StartMovingLeft&);
    void onStopMovingLeft(events::StopMovingLeft&);
    void onStartMovingRight(events::StartMovingRight&);
    void onStopMovingRight(events::StopMovingRight&);
    void onReturnToMenu(events::ReturnToMenu&);

    bool m_moveLeft{false};
    bool m_moveRight{false};
    bool m_gameOver{false};

    Wall m_topWall;
    Wall m_leftWall;
    Wall m_rightWall;
    Paddle m_paddle;
    Ball m_ball;
    Score m_score;
    LifePoints m_lifePoints;
    GameOverState m_gameOverState;

    std::vector<Brick> m_bricks;
    std::vector<std::reference_wrapper<Entity>> m_entities;
    std::shared_ptr<events::EventManager> m_eventManager;
};