//
// Created by zeitgeist on 05.10.23.
//

#pragma once

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>

namespace events {
struct Event {
    Event() = default;
    Event(const Event&) = delete;
    Event(Event&&) = delete;
    Event operator=(const Event&) = delete;
    Event operator=(Event&&) = delete;
    virtual ~Event() = default;
};

struct KeyPress : Event {
    using KeyEventType = decltype(SDL_Event::type);

    explicit KeyPress(KeyEventType keyEvent, SDL_Keycode code)
        : m_code(code)
        , m_keyEvent(keyEvent) {
    }

    SDL_Keycode m_code{};
    KeyEventType m_keyEvent{};
};

struct IncreaseScore : Event {

    explicit IncreaseScore(int value)
        : m_value(value) {
    }

    int m_value;
};

struct Shutdown : Event {};
struct StartStop : Event {};
struct GameOver : Event {};
struct GameStarted : Event {};
struct StartMovingLeft : Event {};
struct StopMovingLeft: Event {};
struct StartMovingRight: Event {};
struct StopMovingRight : Event {};
struct ReturnToMenu : Event {};

}
