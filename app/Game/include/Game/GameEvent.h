#pragma once

#include <Engine/Event.h>
#include <Engine/Entity.h>

class Brick;

namespace events {

    struct BrickDestroyed : Event {
        explicit BrickDestroyed(const Brick& brick) : brick(brick) {}
        const Brick& brick;
    };

    struct BallOutOfBounds : Event {
    };

}

