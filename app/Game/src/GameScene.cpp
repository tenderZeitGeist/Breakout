//
// Created by zeitgeist on 06.10.23.
//

#include <SDL2/SDL.h>

#include "Game/Game.h"
#include "Game/GameScene.h"

#include <Engine/Configuration.h>
#include <iostream>

namespace {
    std::reference_wrapper<Entity> toReference(Entity& e) {
        return e;
    }
}

GameScene::GameScene(Game& game)
    : m_game(game) {
    initializeWalls();
    initializePaddle();
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

void GameScene::initializePaddle() {
    m_paddle.init({
            .x = config::windowHalfWidth - config::slotHalfWidth,
            .y = config::windowHeight - 100,
            .width = config::slotWidth,
            .height = config::slotHeight,
            .velocity = static_cast<float>(config::windowHeight) / 1350.f,
            .color = {0x00, 0xff, 0xff, 0xff}
        }

    );
    m_paddle.setWalls({m_leftWall, m_rightWall});
    m_entities.emplace_back(static_cast<Entity&>(m_paddle));
}

void GameScene::initializeWalls() {
    m_topWall.init({
        .x = 0,
        .y = 0,
        .width = config::windowWidth,
        .height = config::slotHeight
    });

    m_entities.emplace_back(static_cast<Entity&>(m_topWall));

    m_leftWall.init({
        .x = 0,
        .y = 0,
        .width = config::slotWidth,
        .height = config::windowHeight
    });

    m_entities.emplace_back(static_cast<Entity&>(m_leftWall));

    m_rightWall.init({
        .x = config::windowWidth - config::slotHeight,
        .y = 0,
        .width = config::slotWidth,
        .height = config::windowHeight
    });

    m_entities.emplace_back(static_cast<Entity&>(m_rightWall));
}

void GameScene::setPaddleDirection() const {
    const auto keyStates = m_game.getKeyHandler().getKeyStates();
    const float leftDirection = static_cast<float>(keyStates[KeyHandler::kLeft]) * -1.f;
    const float rightDirection = static_cast<float>(keyStates[KeyHandler::kRight]) * 1.f;
    m_paddle.getMoveable()->setDirectionX(leftDirection + rightDirection);
}
