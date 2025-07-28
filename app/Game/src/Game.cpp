//
// Created by zeitgeist on 13.06.23.
//

#include "Game/Game.h"
#include "Game/GameScene.h"
#include "Game/MenuScene.h"
#include "Game/GameEvent.h"

#include <Engine/Event.h>
#include <Engine/EventManager.h>

#include <array>
#include <memory>

#include <iostream>

namespace {

static constexpr std::array<inputs::KeyBinding, inputs::Keys::NUM_OF_KEYS> kBindings = {{
        {inputs::InputEvent::NONE, inputs::InputEvent::NONE}, // KeyHandler::ENTER
        {inputs::InputEvent::INCREASE_SCORE, inputs::InputEvent::NONE}, // KeyHandler::_1
        {inputs::InputEvent::INCREASE_SCORE, inputs::InputEvent::NONE}, // KeyHandler::_2
        {inputs::InputEvent::INCREASE_SCORE, inputs::InputEvent::NONE}, // KeyHandler::_3
        {inputs::InputEvent::START_MOVE_LEFT, inputs::InputEvent::STOP_MOVE_LEFT}, // KeyHandler::LEFT
        {inputs::InputEvent::START_MOVE_RIGHT, inputs::InputEvent::STOP_MOVE_RIGHT}, // KeyHandler::RIGHT
        {inputs::InputEvent::SHOW_DEBUG, inputs::InputEvent::NONE}, // KeyHandler::D
        {inputs::InputEvent::START_STOP, inputs::InputEvent::NONE}, // KeyHandler::SPACE
        {inputs::InputEvent::START_GAME, inputs::InputEvent::NONE}, // KeyHandler::ENTER
}};

}

Game::Game(std::shared_ptr<events::EventManager> eventManager,
           std::reference_wrapper<const inputs::KeyHandler> keyHandler)
    : m_eventManager(std::move(eventManager))
    , m_keyHandler(keyHandler) {
    m_eventManager->subscribe<Game, events::GameOver, &Game::onGameOver>(this);
    m_eventManager->subscribe<Game, events::BallOutOfBounds, &Game::onBallOutOfBounds>(this);
    m_activeScene = m_menuScene.get();
}

void Game::update(float delta) {
    queryInputs();
    updateGame(delta);

    switch (m_state) {
        case State::STOPPED:
            resetGame();
            break;
        case State::INITIALIZED:
            startGame();
            break;
        case State::RUNNING:
        case State::UNINITIALIZED:
        default:
            break;
    }
}

void Game::render(SDL_Renderer& renderer) {
    if (m_activeScene) {
        m_activeScene->render(renderer);
    }
}

void Game::initializeGame(const TextureRenderer& textureRenderer) {
    m_menuScene = std::make_unique<MenuScene>(m_eventManager, textureRenderer);
    m_gameScene = std::make_unique<GameScene>(m_eventManager);
    m_activeScene = m_menuScene.get();
    m_state = State::INITIALIZED;
}

void Game::startGame() {
    if (!m_started) {
        return;
    }
    m_started = false;
    m_activeScene = m_gameScene.get();
    m_state = State::RUNNING;
}

void Game::resetGame() {
    m_activeScene->reset();
    m_activeScene = m_menuScene.get();
    m_playing = false;
    m_state = State::INITIALIZED;
}

void Game::updateGame(float delta) {
    if (!m_playing) {
        return;
    }

    if (m_activeScene) {
        m_activeScene->update(delta);
    }
}

void Game::togglePlayingState() {
    m_playing = !m_playing;
}

void Game::onDebug() {
    m_debug = !m_debug;
    if (m_activeScene) {
        m_activeScene->onDebug(m_debug);
    }
}

void Game::onBallOutOfBounds(events::BallOutOfBounds&) {
    togglePlayingState();
}

void Game::onStartGame() {
    m_started = true;
}

void Game::onGameOver(events::GameOver&) {
    m_state = State::STOPPED;
}

void Game::queryInputs() {
    using namespace inputs;
    const auto& keyStates = m_keyHandler.get().getKeyStates();

    for (std::uint_fast8_t key = 0; key < NUM_OF_KEYS; ++key) {
        const auto inputKey = static_cast<inputs::Keys>(key);
        const bool pressed = keyStates[key];
        const bool pressedBefore = m_pressedKeys.contains(inputKey);

        if (pressed && !pressedBefore) {
            triggerEvent(kBindings[key].onPress);
            m_pressedKeys.insert(inputKey);
        }

        if (!pressed && pressedBefore) {
            triggerEvent(kBindings[key].onRelease);
            m_pressedKeys.erase(inputKey);
        }
    }
}

void Game::triggerEvent(inputs::InputEvent inputEvent) {
    using namespace inputs;
    switch (inputEvent) {
        case inputs::InputEvent::START_MOVE_LEFT:
            m_eventManager->notify(events::StartMovingLeft());
            break;
        case inputs::InputEvent::STOP_MOVE_LEFT:
            m_eventManager->notify(events::StopMovingLeft());
            break;
        case inputs::InputEvent::START_MOVE_RIGHT:
            m_eventManager->notify(events::StartMovingRight());
            break;
        case inputs::InputEvent::STOP_MOVE_RIGHT:
            m_eventManager->notify(events::StopMovingRight());
            break;
        case inputs::InputEvent::SHOW_DEBUG:
            onDebug();
            break;
        case inputs::InputEvent::START_STOP:
            togglePlayingState();
            break;
        case inputs::InputEvent::START_GAME:
            onStartGame();
            break;
        case inputs::InputEvent::NONE:
        default:
            break;
    }
}
