#pragma once

#include <Engine/Entity.h>

class Brick
    : public Entity {
public:
    explicit Brick();

    void reset() override;

    [[nodiscard]] int getValue() const;
    void setValue(int value);

private:
    int m_value{1};
};
