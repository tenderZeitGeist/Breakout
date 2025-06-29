//
// Created by zeitgeist on 13.06.23.
//

#include "Game/Game.h"
#include "Game/GameScene.h"
#include "Game/Scene.h"

#include <SDL2/SDL_render.h>

#include <Engine/Event.h>
#include <Engine/EventManager.h>

#include <memory>

Game::Game(std::shared_ptr<events::EventManager> eventManager, std::reference_wrapper<const KeyHandler> keyHandler)
    : m_eventManager(std::move(eventManager))
    , m_keyHandler(keyHandler)
    , m_scene(std::make_unique<GameScene>(m_keyHandler, m_eventManager)) {

    m_eventManager->subscribe<Game, events::Debug, &Game::onDebug>(this);
    m_eventManager->subscribe<Game, events::StartStop, &Game::onStartStop>(this);
    m_eventManager->subscribe<Game, events::GameOver, &Game::onGameOver>(this);
    m_eventManager->subscribe<Game, events::GameStarted, &Game::onGameStarted>(this);
}

void Game::update(float delta) {
    switch (m_state) {
        case State::STOPPED:
            resetGame();
            break;
        case State::RUNNING:
            updateGame(delta);
            break;
        default:
            break;
    }
}

void Game::render(SDL_Renderer& renderer) {
    if (m_scene) {
        m_scene->render(renderer);
    }
}

void Game::initializeGame() {
    m_scene = std::make_unique<GameScene>(m_keyHandler, m_eventManager);
    m_state = State::RUNNING;
}

void Game::resetGame() {
    // TODO: Switch back to game menu scene
    initializeGame();
}

void Game::updateGame(float delta) {
    if (!m_playing) {
        return;
    }

    if (m_scene) {
        m_scene->update(delta);
    }
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

void Game::onGameStarted(events::GameStarted&) {
    m_playing = false;
    // TODO: This clean-up introduces UB during update() and needs to be taken care of.
    m_scene = std::make_unique<GameScene>(m_keyHandler, m_eventManager);
    m_state = State::INITIALIZED;
}

void Game::onGameOver(events::GameOver&) {
    m_playing = false;
    m_state = State::STOPPED;
}
