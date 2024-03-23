//
// Created by zeitgeist on 06.10.23.
//

#pragma once

#include "Brick.h"
#include "Scene.h"
#include "Paddle.h"
#include "Wall.h"

#include <vector>

class Entity;
class Game;

class GameScene
    : public Scene {
public:
    explicit GameScene(Game& game);

    void update(float delta) override;
    void render(SDL_Renderer& renderer) override;
    void enter() override;
    void exit() override;

private:
    void initializePaddle();
    void initializeWalls();
    void initializeBricks();
    void setPaddleDirection() const;

    Game& m_game;
    Wall m_topWall;
    Wall m_leftWall;
    Wall m_rightWall;
    Paddle m_paddle;
    std::vector<Brick> m_bricks;
    std::vector<std::reference_wrapper<Entity>> m_entities;
};