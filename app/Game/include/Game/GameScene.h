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
}

class GameScene
    : public Scene {
public:
    explicit GameScene(std::shared_ptr<events::EventManager> eventManager);
    ~GameScene() override;

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

    void onBrickDestroyed(events::BrickDestroyed& e);
    void onBallOutOfBounds(events::BallOutOfBounds&);
    void onIncreaseScore(events::IncreaseScore& e);
    void onStartMovingLeft(events::StartMovingLeft&);
    void onStopMovingLeft(events::StopMovingLeft&);
    void onStartMovingRight(events::StartMovingRight&);
    void onStopMovingRight(events::StopMovingRight&);

    bool m_moveLeft{false};
    bool m_moveRight{false};

    Wall m_topWall;
    Wall m_leftWall;
    Wall m_rightWall;
    Paddle m_paddle;
    Ball m_ball;
    Score m_score;
    LifePoints m_lifePoints;

    std::vector<Brick> m_bricks;
    std::vector<std::reference_wrapper<Entity>> m_entities;
    std::shared_ptr<events::EventManager> m_eventManager;
};