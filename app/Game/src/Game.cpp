//
// Created by zeitgeist on 13.06.23.
//

#include "Game/Game.h"

#include <SDL2/SDL_render.h>

#include <Engine/EventManager.h>
#include <Engine/Event.h>
#include <Game/Scene.h>

#include <iostream>

Game::Game(std::shared_ptr<events::EventManager> eventManager)
    : m_eventManager(std::move(eventManager)) {
    m_eventManager->subscribe<Game, events::KeyPress, &Game::onKeyEvent>(this);
}

void Game::update(float delta) {
    if(m_scene) {
        m_scene->update(delta);
    }
}

void Game::render(SDL_Renderer& renderer) {
    if(m_scene) {
        m_scene->render(renderer);
    }
}

void Game::onKeyEvent(events::KeyPress& e) {
    if (!m_scene) {
        return;
    }

    switch (e.m_keyEvent) {
        case SDL_KEYDOWN:
            m_scene->keyDown(e.m_code);
            break;
        case SDL_KEYUP:
            m_scene->keyUp(e.m_code);
            break;
    }

    std::cerr << "Key Event Type: " << e.m_keyEvent << '\n'
              << "Key Code: " << e.m_code << '\n';
}

void Game::setScene(std::unique_ptr<Scene> scene) {
    m_scene = std::move(scene);
}

const Scene* Game::getScene() const {
   return m_scene.get();
}
