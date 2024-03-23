//
// Created by zeitgeist on 23.03.24.
//

#include "Engine/KeyHandler.h"

#include <cassert>

namespace {
    std::size_t keyCodeToIndex(SDL_Keycode code) {
        switch (code) {
            case SDLK_LEFT:
                return 0;
            case SDLK_RIGHT:
                return 1;
            default:
                break;
        }
        assert("Invalid keycode");
    }
}


const KeyHandler::KeyStateArray& KeyHandler::getKeyStates() const {
    return m_keyStates;
}

void KeyHandler::setKeyState(SDL_Keycode code, bool state) {
    const auto index = keyCodeToIndex(code);
    m_keyStates[index] = state;
}

