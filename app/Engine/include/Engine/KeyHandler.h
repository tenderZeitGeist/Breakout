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
struct IncreaseScore;
class EventManager;
}

namespace inputs {

enum Keys : std::uint_fast8_t {
    INVALID,
    _1,
    _2,
    _3,
    LEFT,
    RIGHT,
    D,
    SPACE,
    ENTER,
    NUM_OF_KEYS
};

enum class InputEvent {
    NONE,
    SHOW_DEBUG,
    START_STOP,
    INCREASE_SCORE,
    START_MOVE_LEFT,
    STOP_MOVE_LEFT,
    START_MOVE_RIGHT,
    STOP_MOVE_RIGHT
};

struct KeyBinding {
    InputEvent onPress;
    InputEvent onRelease;
};

using KeyStateArray = std::array<bool, inputs::Keys::NUM_OF_KEYS>;

class KeyHandler {
public:
    explicit KeyHandler(std::shared_ptr<events::EventManager> eventManager) noexcept;
    void onKeyEvent(events::KeyPress& e);

    [[nodiscard]] const inputs::KeyStateArray& getKeyStates() const;
    void setKeyState(SDL_Keycode code, bool state);

private:
    inputs::KeyStateArray m_keyStates{};
    std::shared_ptr<events::EventManager> m_eventManager;
};

}
