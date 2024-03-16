//
// Created by zeitgeist on 10.10.23.
//

#pragma once

#include <Engine/Entity.h>

class Paddle
    : public Entity {
public:
    Paddle();

    void update(float dt) override;

    void shrink();
    void reset();
private:
    int m_originalWidth;
    int m_currentWidth;
};
