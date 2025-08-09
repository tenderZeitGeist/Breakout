#pragma once

#include <Engine/Event.h>
#include <Engine/Entity.h>

class Brick;

namespace events {

    struct BrickDestroyed : Event {
        explicit BrickDestroyed(std::reference_wrapper<const Brick> brick) : brick(brick) {}
        std::reference_wrapper<const Brick> brick;
    };

    struct BallOutOfBounds : Event {
    };

}

