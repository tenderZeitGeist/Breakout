//
// Created by zeitgeist on 12.10.23.
//

#include "../Paddle.h"

#include <Engine/Configuration.h>

Paddle::Paddle()
    : Entity(DRAWABLE | MOVEABLE | COLLIDEABLE)
    , m_currentWidth(0)
    , m_originalWidth(0) {
}

void Paddle::update(float dt) {
    if (m_moveable) {
        m_moveable->move(dt);
    }
}

void Paddle::shrink() {
    const auto width = getWidth();
    if (m_originalWidth == 0) {
        m_originalWidth = width;
    }

    if(m_originalWidth == width) {
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
