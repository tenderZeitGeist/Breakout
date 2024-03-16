//
// Created by zeitgeist on 11.10.23.
//

#pragma once

class Entity;

class Moveable {
public:
    explicit Moveable(Entity& entity);
    void move(float delta);

    [[nodiscard]] float getDirectionX() const;
    [[nodiscard]] float getDirectionY() const;
    [[nodiscard]] float getVelocity() const;

    void setDirectionX(float x);
    void setDirectionY(float y);
    void setVelocity(float velocity);

private:
    Entity& m_entity;
    float m_directionX;
    float m_directionY;
    float m_velocity;
};