//
// Created by zeitgeist on 13.06.23.
//

#include "Game/Game.h"
#include "Game/Scene.h"

#include <SDL2/SDL_render.h>

#include <Engine/EventManager.h>
#include <Engine/Event.h>

Game::Game(std::shared_ptr<events::EventManager> eventManager)
    : m_eventManager(std::move(eventManager))
      , m_keyHandler(m_eventManager) {
    m_eventManager->subscribe<Game, events::KeyPress, &Game::onKeyEvent>(this);
    m_eventManager->subscribe<Game, events::Debug, &Game::onDebug>(this);
}

void Game::update(float delta) {
    if (m_scene) {
        m_scene->update(delta);
    }
}

void Game::render(SDL_Renderer& renderer) {
    if (m_scene) {
        m_scene->render(renderer);
    }
}

void Game::setScene(std::unique_ptr<Scene> scene) {
    m_scene = std::move(scene);
}

const Scene* Game::getScene() const {
    return m_scene.get();
}

const KeyHandler& Game::getKeyHandler() const {
    return m_keyHandler;
}

void Game::onKeyEvent(events::KeyPress& e) {
    m_keyHandler.onKeyEvent(e);
}

void Game::onDebug(events::Debug&) {
    m_debug = !m_debug;
    if (m_scene) {
        m_scene->onDebug(m_debug);
    }
}
