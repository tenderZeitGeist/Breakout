//
// Created by zeitgeist on 12.10.23.
//

#include "Game/Paddle.h"
#include <Engine/Collidable.h>
#include <Engine/Configuration.h>

Paddle::Paddle()
    : Entity(DRAWABLE | MOVEABLE | COLLIDABLE)
    , m_originalWidth(0)
    , m_currentWidth(0) {
}

void Paddle::update(float dt) {
    const auto previousX = getX();
    m_moveable.move(dt);
    for (const auto wallRef : m_walls) {
        auto& wall = wallRef.get();
        if (wall.getCollidable() == getCollidable()) {
            setX(previousX);
            return;
        }
    }
}

void Paddle::init(Entity::Values v) {
    Entity::init(v);
    setDefaultPosition(v.x, v.y);
    m_originalWidth = getWidth();
}

void Paddle::shrink() {
    const auto width = getWidth();
    if (m_originalWidth != width) {
        return;
    }

    const auto halfWidth = width / 2;
    setWidth(halfWidth);
    setX(getX() + halfWidth / 2);
}

void Paddle::reset() {
    setX(m_defaultX);
    setY(m_defaultY);
    if (m_originalWidth != getWidth()) {
        setWidth(m_originalWidth);
    }
    m_drawable.setVisible(true);
}

void Paddle::setWalls(std::initializer_list<std::reference_wrapper<Wall>> walls) {
    m_walls = walls;
}

void Paddle::setDefaultPosition(int x, int y) {
    m_defaultX = x;
    m_defaultY = y;
}
