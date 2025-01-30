//
// Created by zeitgeist on 13.10.23.
//

#include "Engine/Collideable.h"

#include <cmath>

Collideable::Collideable(Entity& entity){

}

bool operator==(const Collideable& lhs, const Collideable& rhs) {
    return static_cast<bool>(collides(lhs, rhs));
}

bool operator !=(const Collideable& lhs, const Collideable& rhs) {
    return !(lhs == rhs);
}

Collision collides(const Collideable& lhs, const Collideable& rhs) {
    if(!lhs.isEnabled() || !rhs.isEnabled()) {
        return Collision::NONE;
    }

    const auto deltaX = lhs.getCenterX() - rhs.getCenterX();
    const auto deltaY = lhs.getCenterY() - rhs.getCenterY();
    const auto sumOfExtentX = lhs.getExtentX() + rhs.getExtentX();
    const auto sumOfExtentY = lhs.getExtentY() + rhs.getExtentY();
    const auto overlapX = sumOfExtentX - std::abs(deltaX);
    const auto overlapY = sumOfExtentY - std::abs(deltaY);

    if (overlapX <= 0 || overlapY <= 0) {
        return Collision::NONE;
    }

    int collisions = Collision::NONE;
    if (overlapX < overlapY) {
        collisions |= deltaX > 0 ? Collision::RIGHT : Collision::LEFT;
    } else {
        collisions |= deltaY > 0 ? Collision::BOTTOM : Collision::TOP;
    }

    return static_cast<Collision>(collisions);
}

bool Collideable::isEnabled() const {
    return m_enabled;
}

int Collideable::getExtentX() const {
    return m_extentX;
}

int Collideable::getExtentY() const {
    return m_extentY;
}

int Collideable::getCenterX() const {
    return m_centerX;
}

int Collideable::getCenterY() const {
    return m_centerY;
}

void Collideable::setEnabled(bool enabled) {
    m_enabled = enabled;
}

void Collideable::setExtentX(int extentX) {
    m_extentX = extentX;
}

void Collideable::setExtentY(int extentY) {
    m_extentY = extentY;
}

void Collideable::setCenterX(int centerX) {
    m_centerX = centerX;
}

void Collideable::setCenterY(int centerY) {
     m_centerY = centerY;
}

