//
// Created by zeitgeist on 13.10.23.
//

#include "Engine/Collideable.h"

#include <cmath>

Collideable::Collideable(Entity& entity){

}

bool operator==(const Collideable& lhs, const Collideable& rhs) {
    return collides(lhs, rhs);
}

bool operator !=(const Collideable& lhs, const Collideable& rhs) {
    return !(lhs == rhs);
}

bool collides(const Collideable& lhs, const Collideable& rhs) {
    if(!lhs.isEnabled() || !rhs.isEnabled()) {
        return false;
    }

    // Axis-Aligned Bounding Box intersection test.
    const auto x = std::abs(lhs.getCenterX() - rhs.getCenterX()) < (lhs.getExtentX() + rhs.getExtentX());
    const auto y = std::abs(lhs.getCenterY() - rhs.getCenterY()) < (lhs.getExtentY() + rhs.getExtentY());
    return x && y;
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


