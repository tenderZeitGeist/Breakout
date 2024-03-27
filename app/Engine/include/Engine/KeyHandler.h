//
// Created by zeitgeist on 23.03.24.
//

#pragma once

#include <SDL2/SDL_keycode.h>

#include <array>
#include <cstdint>
#include <memory>

namespace events {
    struct KeyPress;
    class EventManager;
}

class KeyHandler {
public:
    enum Keys : std::int_fast8_t {
        LEFT,
        RIGHT,
        D,
        SPACE,
        INVALID,
        NUM_OF_KEYS
    };

    using KeyStateArray = std::array<bool, NUM_OF_KEYS>;

    explicit KeyHandler(std::shared_ptr<events::EventManager> eventManager) noexcept;
    void onKeyEvent(events::KeyPress& e);

    [[nodiscard]] const KeyStateArray& getKeyStates() const;
    void setKeyState(SDL_Keycode code, bool state);

private:
    KeyStateArray m_keyStates{};
    std::shared_ptr<events::EventManager> m_eventManager;
};
