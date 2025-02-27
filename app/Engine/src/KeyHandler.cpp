//
// Created by zeitgeist on 23.03.24.
//

#include "Engine/KeyHandler.h"
#include "Engine/EventManager.h"

#include <cassert>

namespace {
    std::size_t keyCodeToIndex(SDL_Keycode code) {
        switch (code) {
            case SDLK_LEFT:
                return KeyHandler::LEFT;
            case SDLK_RIGHT:
                return KeyHandler::RIGHT;
            case SDLK_d:
                return KeyHandler::D;
            case SDLK_SPACE:
                return KeyHandler::SPACE;
        }
        return KeyHandler::INVALID;
    }
}


KeyHandler::KeyHandler(std::shared_ptr<events::EventManager> eventManager) noexcept
    : m_eventManager(std::move(eventManager)) {
    m_eventManager->subscribe<KeyHandler, events::KeyPress, &KeyHandler::onKeyEvent>(this);
}

void KeyHandler::onKeyEvent(events::KeyPress& e) {
    setKeyState(e.m_code, e.m_keyEvent == SDL_KEYDOWN);

    if (m_keyStates[D]) {
        m_eventManager->notify(events::Debug());
    }

    if (m_keyStates[SPACE]) {
        m_eventManager->notify(events::StartStop());
    }
}

const KeyHandler::KeyStateArray& KeyHandler::getKeyStates() const {
    return m_keyStates;
}

void KeyHandler::setKeyState(SDL_Keycode code, bool state) {
    const auto index = keyCodeToIndex(code);
    m_keyStates[index] = state;
}

