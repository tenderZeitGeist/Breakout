//
// Created by zeitgeist on 27.03.24.
//
#pragma once

#include <Engine/Entity.h>

class Ball
    : public Entity {
public:
    Ball();
    void update(float delta) override;
    void init(Values v) override;
    void onDebug(bool debug) override;
    void reset();

private:
    std::size_t m_hitCount{0};
    bool m_orangeBrickHit{false};
    bool m_redBrickHit{false};
};
