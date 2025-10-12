#include <Engine/KeyHandler.h>
#include <Engine/EventManager.h>

#include <cassert>

namespace {
std::size_t keyCodeToIndex(SDL_Keycode code) {
    switch (code) {
        case SDLK_1:
            return inputs::Keys::_1;
        case SDLK_2:
            return inputs::Keys::_2;
        case SDLK_3:
            return inputs::Keys::_3;
        case SDLK_4:
            return inputs::Keys::_4;
        case SDLK_LEFT:
            return inputs::Keys::LEFT;
        case SDLK_RIGHT:
            return inputs::Keys::RIGHT;
        case SDLK_d:
            return inputs::Keys::D;
        case SDLK_SPACE:
            return inputs::Keys::SPACE;
        case SDLK_RETURN:
            return inputs::Keys::ENTER;
    }
    return inputs::Keys::INVALID;
}
}

namespace inputs {

KeyHandler::KeyHandler(std::shared_ptr<events::EventManager> eventManager) noexcept
    : m_eventManager(std::move(eventManager)) {
    m_eventManager->subscribe<KeyHandler, events::KeyPress, &KeyHandler::onKeyEvent>(this);
}

void KeyHandler::onKeyEvent(events::KeyPress& e) {
    setKeyState(e.m_code, e.m_keyEvent == SDL_KEYDOWN);
}

const KeyStateArray& KeyHandler::getKeyStates() const {
    return m_keyStates;
}

void KeyHandler::setKeyState(SDL_Keycode code, bool state) {
    const auto index = keyCodeToIndex(code);
    m_keyStates[index] = state;
}

}
