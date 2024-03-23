//
// Created by zeitgeist on 06.10.23.
//

#pragma once

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
    void keyDown(SDL_Keycode code) override;
    void keyUp(SDL_Keycode code) override;

private:
    void initializePaddle();
    void initializeWalls();
    void setPaddleDirection() const;

    Game& m_game;
    Wall m_topWall;
    Wall m_leftWall;
    Wall m_rightWall;
    Paddle m_paddle;
    std::vector<std::reference_wrapper<Entity>> m_entities;
};