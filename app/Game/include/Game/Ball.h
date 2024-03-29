//
// Created by zeitgeist on 27.03.24.
//
#pragma once

#include <Engine/Entity.h>

#include <vector>

class Brick;
class Paddle;
class Wall;

class Ball
    : public Entity {
public:
    explicit Ball(Paddle& paddle);
    void update(float delta) override;
    void init(Values v) override;
    void onDebug(bool debug) override;
    void reset();

    void setWalls(std::vector<std::reference_wrapper<Wall>> walls);
    void setBricks(std::vector<std::reference_wrapper<Brick>> bricks);
    [[nodiscard]] static constexpr float initialVelocity();

private:
    std::vector<std::reference_wrapper<Wall>> m_walls;
    std::vector<std::reference_wrapper<Brick>> m_bricks;
    Paddle& m_paddle;
    std::size_t m_hitCount{0};
    bool m_orangeBrickHit{false};
    bool m_redBrickHit{false};
};
