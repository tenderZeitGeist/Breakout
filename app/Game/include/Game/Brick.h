
#pragma once

#include <Engine/Entity.h>

class Brick
: public Entity
{
public:
    explicit Brick();
    Brick(Brick&&) = default;
    Brick& operator=(Brick&&) = default;
};
