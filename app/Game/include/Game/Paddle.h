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
    void shrink();
    void reset();

    void setWalls(std::initializer_list<std::reference_wrapper<Wall>> walls);

private:
    int m_originalWidth;
    int m_currentWidth;
    std::vector<std::reference_wrapper<Wall>> m_walls;
};
