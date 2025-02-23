//
// Created by zeitgeist on 10.10.23.
//

#pragma once

#include <Engine/Entity.h>

#include <vector>

#include "Wall.h"

class Paddle
    : public Entity {
public:
    Paddle();
    void update(float dt) override;
    void init(Entity::Values v) override;
    void shrink();
    void reset();

    void setWalls(std::initializer_list<std::reference_wrapper<Wall>> walls);

private:
    void setDefaultPosition(int x, int y);

    int m_defaultX{0};
    int m_defaultY{0};
    int m_originalWidth{0};
    int m_currentWidth{0};
    std::vector<std::reference_wrapper<Wall>> m_walls;
};
