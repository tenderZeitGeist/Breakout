#pragma once

#include <Engine/Entity.h>

class Brick
    : public Entity {
public:
    explicit Brick();

    void reset() override;

    [[nodiscard]] int getValue() const;

private:
    int m_value{1};
};
