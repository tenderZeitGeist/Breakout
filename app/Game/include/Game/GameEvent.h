#pragma once

#include <Engine/Event.h>
#include <Engine/Entity.h>

class Brick;

namespace events {

    struct BrickDestroyedEvent : Event {
        explicit BrickDestroyedEvent(const Brick& brick) : brick(brick) {}
        const Brick& brick;
    };

    struct BallOutOfBoundsEvent : Event {
    };

}

