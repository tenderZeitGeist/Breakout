//
// Created by zeitgeist on 12.10.23.
//

#include "Game/Paddle.h"

#include <Engine/Configuration.h>

Paddle::Paddle()
    : Entity(DRAWABLE | MOVEABLE | COLLIDEABLE)
    , m_currentWidth(0)
    , m_originalWidth(0) {
}

void Paddle::update(float dt) {
    m_moveable->move(dt);
    for (const auto wallRef: m_walls) {
        const auto& wall = wallRef.get();
        const auto collision = collides(*wall.getCollideable(), *m_collideable);
        if (!collision) {
            continue;
        }

        if (collision & Collision::LEFT) {
            setX(wall.getX() + wall.getWidth());
        }
        if (collision & Collision::RIGHT) {
            setX(wall.getX() - getWidth());
        }
    }
}

void Paddle::init(Entity::Values v) {
    Entity::init(v);
    m_defaultX = v.x;
    m_defaultY = v.y;
    m_originalWidth =  v.width;
}

void Paddle::shrink() {
    const auto width = getWidth();
    if (m_originalWidth == 0) {
        m_originalWidth = width;
    }

    if (m_originalWidth == width) {
        const auto halfWidth = width / 2;
        setWidth(halfWidth);
        setX(getX() + halfWidth / 2);
    }
}

void Paddle::reset() {
    setX(m_defaultX);
    setY(m_defaultY);

    if (m_originalWidth == getWidth()) {
        return;
    }

    setWidth(m_originalWidth);
}

void Paddle::setWalls(std::initializer_list<std::reference_wrapper<Wall> > walls) {
    m_walls = walls;
}