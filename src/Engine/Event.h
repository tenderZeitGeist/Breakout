//
// Created by zeitgeist on 05.10.23.
//

#pragma once
namespace events {
    struct Event {
    public:
        virtual ~Event() = default;
    };

    struct Shutdown
        : public Event {
    };

    struct KeyDown
        : public Event {

    };

    struct KeyUp
        : public Event {
    };
}