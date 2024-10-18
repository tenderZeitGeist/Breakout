
#pragma once

#include <Engine/Entity.h>

class Brick
    : public Entity {
public:
    explicit Brick();
    Brick(Brick&&) = default;
    Brick& operator=(Brick&&) = default;
    [[nodiscard]] std::size_t getValue() const;

private:
    std::size_t m_value{1};
};
