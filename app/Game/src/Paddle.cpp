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
    const int currentX = getX();
    m_moveable->move(dt);
    for (const auto wallRef: m_walls) {
        const auto& wall = wallRef.get();
        if (*wall.getCollideable() != *m_collideable) {
           continue;
        }
        setX(currentX);
        return;
    }
}

void Paddle::init(Entity::Values v) {
    Entity::init(v);
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
    if (m_originalWidth != 0 && m_originalWidth != getWidth()) {
        setWidth(m_originalWidth);
        setX(config::windowWidth / 2 - m_originalWidth / 2);
    }
}

void Paddle::setWalls(std::initializer_list<std::reference_wrapper<Wall> > walls) {
    m_walls = walls;
}
