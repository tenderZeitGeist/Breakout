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
class KeyHandler;

namespace events {
    class EventManager;
    struct BrickDestroyedEvent;
    struct BallOutOfBoundsEvent;
}

class GameScene
    : public Scene {
public:
    explicit GameScene(std::reference_wrapper<const KeyHandler> keyHandler, std::shared_ptr<events::EventManager> eventManager);
    ~GameScene() override;

    void update(float delta) override;
    void render(SDL_Renderer& renderer) override;
    void enter() override;
    void exit() override;

    void onDebug(bool debug) override;

    void onBrickDestroyed(events::BrickDestroyedEvent& e);
    void onBallOutOfBounds(events::BallOutOfBoundsEvent& e);
    void onIncreaseScore(events::IncreaseScore& e);

private:
    void initializePaddle();
    void initializeWalls();
    void initializeBricks();
    void initializeBall();
    void initializeScore();
    void initializeLifePoints();
    void setPaddleDirection() const;

    int m_pointCounter{0};

    Wall m_topWall;
    Wall m_leftWall;
    Wall m_rightWall;
    Paddle m_paddle;
    Ball m_ball;
    Score m_score;
    LifePoints m_lifePoints;

    std::vector<Brick> m_bricks;
    std::vector<std::reference_wrapper<Entity>> m_entities;
    std::reference_wrapper<const KeyHandler> m_keyHandler;
    std::shared_ptr<events::EventManager> m_eventManager;
};