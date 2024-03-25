//
// Created by zeitgeist on 06.10.23.
//

#include <SDL2/SDL.h>

#include "Game/Game.h"
#include "Game/GameScene.h"

#include <Engine/Configuration.h>
#include <iostream>

GameScene::GameScene(Game& game)
    : m_game(game) {
    initializeWalls();
    initializeBricks();
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
    m_entities.emplace_back(m_paddle);
}

void GameScene::initializeWalls() {
    m_topWall.init({
        .x = 0,
        .y = 0,
        .width = config::windowWidth,
        .height = config::slotHeight
    });

    m_entities.emplace_back(m_topWall);

    m_leftWall.init({
        .x = 0,
        .y = 0,
        .width = config::slotWidth,
        .height = config::windowHeight
    });

    m_entities.emplace_back(m_leftWall);

    m_rightWall.init({
        .x = config::windowWidth - config::slotHeight,
        .y = 0,
        .width = config::slotWidth,
        .height = config::windowHeight
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

void GameScene::setPaddleDirection() const {
    const auto& keyStates = m_game.getKeyHandler().getKeyStates();
    const float leftDirection = static_cast<float>(keyStates[KeyHandler::kLeft]) * -1.f;
    const float rightDirection = static_cast<float>(keyStates[KeyHandler::kRight]) * 1.f;
    m_paddle.getMoveable()->setDirectionX(leftDirection + rightDirection);
}
