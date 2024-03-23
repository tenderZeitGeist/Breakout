//
// Created by zeitgeist on 23.03.24.
//

#pragma once

#include <array>
#include <SDL2/SDL_keycode.h>

class KeyHandler {
public:
    using KeyStateArray = std::array<bool, 2>;
    static constexpr std::size_t kLeft = 0;
    static constexpr std::size_t kRight = 1;

    [[nodiscard]] const KeyStateArray& getKeyStates() const;
    void setKeyState(SDL_Keycode code, bool state);

private:
    KeyStateArray m_keyStates{};
};
