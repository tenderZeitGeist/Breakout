//
// Created by zeitgeist on 27.03.24.
//
#pragma once

#include <Engine/Entity.h>

#include <vector>

class Paddle;
class Wall;
class Vector2D;

class Ball
    : public Entity {
public:
    explicit Ball(Paddle& paddle);
    void update(float delta) override;
    void init(Values v) override;
    void onDebug(bool debug) override;
    void reset();

    void setWalls(std::initializer_list<std::reference_wrapper<Wall>> walls);
    [[nodiscard]] static constexpr float initialVelocity() ;

private:
    void calculateNewDirection();
    std::vector<std::reference_wrapper<Wall>> m_walls;
    Paddle& m_paddle;
    std::size_t m_hitCount{0};
    bool m_orangeBrickHit{false};
    bool m_redBrickHit{false};
};
