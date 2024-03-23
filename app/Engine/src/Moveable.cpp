//
// Created by zeitgeist on 11.10.23.
//

#include "Engine/Entity.h"
#include "Engine/Moveable.h"

#include <cmath>

Moveable::Moveable(Entity& entity)
    : m_entity(entity)
    , m_directionX(0.f)
    , m_directionY(0.f)
    , m_velocity(0.f) {

}

void Moveable::move(float delta) {
    const auto diffX = static_cast<int>(delta * m_directionX * m_velocity);
    m_entity.setX(m_entity.getX() + diffX);
    const auto diffY = static_cast<int>(delta * m_directionY * m_velocity);
    m_entity.setY(m_entity.getY() + diffY);
}

float Moveable::getDirectionX() const {
    return m_directionX;
}

float Moveable::getDirectionY() const {
    return m_directionY;
}

float Moveable::getVelocity() const {
    return m_velocity;
}

void Moveable::setDirectionX(float x) {
    m_directionX = x;
}

void Moveable::setDirectionY(float y) {
    m_directionY = y;
}

void Moveable::setVelocity(float velocity) {
    m_velocity = velocity;
}
