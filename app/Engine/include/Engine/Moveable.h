//
// Created by zeitgeist on 11.10.23.
//

#pragma once

#include <Engine/Component.h>

class Entity;
struct Vector2D;

class Moveable : public Component {
public:
    explicit Moveable(Entity& entity);
    void move(float delta);

    [[nodiscard]] float getDirectionX() const;
    [[nodiscard]] float getDirectionY() const;
    [[nodiscard]] Vector2D getDirection() const;
    [[nodiscard]] float getVelocity() const;

    void setDirectionX(float x);
    void setDirectionY(float y);
    void setDirection(Vector2D vector);
    void setVelocity(float velocity);

    [[nodiscard]] float currentDirection() const;

private:
    Entity& m_entity;
    float m_directionX;
    float m_directionY;
    float m_velocity;
};