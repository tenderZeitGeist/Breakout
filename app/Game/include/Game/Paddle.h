
#pragma once

#include <Engine/Entity.h>
#include <Game/Wall.h>

#include <vector>


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
