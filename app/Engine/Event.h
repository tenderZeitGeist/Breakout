//
// Created by zeitgeist on 05.10.23.
//

#pragma once

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>

namespace events {
    struct Event {
    public:
        Event() = default;
        Event(const Event&) = delete;
        Event(Event&&) = delete;
        Event operator=(const Event&) = delete;
        Event operator=(Event&&) = delete;
        virtual ~Event() = default;
    };

    struct Shutdown
        : public Event {
    };

    struct KeyPress
        : public Event {

        using KeyEventType = decltype(SDL_Event::type);

        explicit KeyPress(KeyEventType keyEvent, SDL_Keycode code)
            : m_keyEvent(keyEvent)
            , m_code(code) {}

        SDL_Keycode m_code{};
        KeyEventType m_keyEvent{};
    };

}