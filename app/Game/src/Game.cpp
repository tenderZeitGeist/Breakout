//
// Created by zeitgeist on 13.06.23.
//

#include "Game/Game.h"
#include "Game/Scene.h"

#include <SDL2/SDL_render.h>

#include <Engine/EventManager.h>
#include <Engine/Event.h>

Game::Game(std::shared_ptr<events::EventManager> eventManager)
    : m_eventManager(std::move(eventManager)) {
    m_eventManager->subscribe<Game, events::Debug, &Game::onDebug>(this);
    m_eventManager->subscribe<Game, events::StartStop, &Game::onStartStop>(this);
}

void Game::update(float delta) {
    if(!m_playing) {
        return;
    }

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

void Game::onDebug(events::Debug&) {
    m_debug = !m_debug;
    if (m_scene) {
        m_scene->onDebug(m_debug);
    }
}

void Game::onStartStop(events::StartStop&) {
    m_playing = !m_playing;
}
