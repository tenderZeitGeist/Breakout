//
// Created by zeitgeist on 06.10.23.
//

#include <SDL2/SDL.h>

#include "Game.h"
#include "GameScene.h"

#include <Engine/Configuration.h>
#include <Engine/Drawable.h>
#include <Engine/Moveable.h>
#include <iostream>

GameScene::GameScene(Game& game)
    : m_game(game)
    , m_paddle() {
    initializePaddle();
}

void GameScene::update(float delta) {
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

void GameScene::keyDown(SDL_Keycode code) {
    auto paddleMoveComponent = m_paddle.getMoveable();
    switch (code) {
        case SDLK_LEFT:
            paddleMoveComponent->setDirectionX(-1.f);
            break;
        case SDLK_RIGHT:
            paddleMoveComponent->setDirectionX(1.f);
            break;
        default:
            break;
    }
}

void GameScene::keyUp(SDL_Keycode code) {
    auto paddleMoveComponent = m_paddle.getMoveable();
    switch (code) {
        case SDLK_LEFT:
            if (std::fabs(paddleMoveComponent->getDirectionX() + 1.f) < 0.00001f)
                paddleMoveComponent->setDirectionX(0.f);
            break;
        case SDLK_RIGHT:
            if (std::fabs(paddleMoveComponent->getDirectionX() - 1.f) < 0.00001f)
                paddleMoveComponent->setDirectionX(0.f);
            break;
        default:
            break;
    }
}

void GameScene::initializePaddle() {
    m_paddle.init({
                      .x = config::windowHalfWidth - config::slotHalfWidth,
                      .y = config::windowHeight - 100,
                      .width = config::slotWidth,
                      .height = config::slotHeight,
                      .velocity = static_cast<float>(config::windowHeight) / 1350.f,
                      .color = {0x00, 0xff, 0xff, 0xff}
                  });

    m_entities.emplace_back(static_cast<Entity&>(m_paddle));
}
