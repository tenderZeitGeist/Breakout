//
// Created by zeitgeist on 27.03.24.
//

#include "Game/Ball.h"

#include <algorithm>

#include "Game/Wall.h"

#include <Engine/Configuration.h>

#include <cassert>
#include <random>
#include <cmath>
#include <iostream>

#include "Game/Paddle.h"

struct Vector2D {
    float x;
    float y;
};

namespace {
    float magnitude(float x, float y) {
        return std::sqrt(x * x + y * y);
    }

    float magnitude(Vector2D v) {
        return magnitude(v.x, v.y);
    }

    Vector2D normalize(const Vector2D vector) {
        const auto x = vector.x;
        const auto y = vector.y;
        const auto length = magnitude(x, y);
        return {x / length, y / length};
    }

    Vector2D generateRandomDirection() {
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution distribution(1, 3);

        const Vector2D direction = [value = distribution(rng)]() -> Vector2D {
            switch (value) {
                case 1:
                // return {0.f, 1.f};
                case 2:
                    return {0.5f, 0.5f};
                case 3:
                    return {-0.5f, 0.5f};
                default:
                    break;
            }
            assert("Invalid number generated");
            return {};
        }();
        return direction;
    }

    Vector2D rotate(Vector2D velocity, float theta) {
        const auto vx = velocity.x * std::cos(theta) - velocity.y * std::sin(theta);
        const auto vy = velocity.x * std::sin(theta) + velocity.y * std::cos(theta);
        std::cerr << vx << "\t" << vy << '\n';
        return {vx, vy};
    }

    float reflection(Vector2D v1, Vector2D v2) {
        const float dotProduct = v1.x * v2.x + v1.y * v2.y;
        const float magnitudeProduct = magnitude(v1) * magnitude(v2);
        const float theta = -std::acos(dotProduct / magnitudeProduct);
        return theta;
    }

    Vector2D calculateDirection(Vector2D v1, Vector2D v2) {
        const auto theta = reflection(v1, v2);
        std::cerr << theta << "\t" << theta * (180.0 / std::numbers::pi) << '\n';
        const auto direction = rotate({v1.x, v1.y}, theta);
        return normalize(direction);
    }
}

Ball::Ball(Paddle& paddle)
: Entity(COLLIDEABLE | DRAWABLE | MOVEABLE, Drawable::Shape::CIRCLE)
, m_paddle(paddle) {
}

void Ball::update(float delta) {
    const auto x = getX();
    const auto y = getY();
    m_moveable->move(delta);
    const auto resetPosition = [this](int x, int y) {
        setX(x);
        setY(y);
    };

    for (auto wallRef: m_walls) {
        const auto& wall = wallRef.get();
        if (*wall.getCollideable() == *m_collideable) {
            resetPosition(x, y);
            const auto wallNormals = wall.getNormals();
            const auto xDir = wallNormals.first != 0.f;
            if (xDir) {
                m_moveable->setDirectionX(m_moveable->getDirectionX() * -1.f);
            } else {
                m_moveable->setDirectionY(m_moveable->getDirectionY() * -1.f);
            }
            return;
        }
    }

    const auto& paddle = *m_paddle.getCollideable();
    if (*m_collideable == *m_paddle.getCollideable()) {
        resetPosition(x, y);
        const auto distance = static_cast<float>(m_collideable->getCenterX() - paddle.getCenterX());
        const auto dx = distance / (static_cast<float>(m_paddle.getWidth()) / 2.f);
        Vector2D direction = normalize({dx, -m_moveable->getDirectionY()});
        m_moveable->setDirectionX(direction.x);
        m_moveable->setDirectionY(direction.y);
    }
}

void Ball::init(Values v) {
    Entity::init(v);
    assert(getWidth() == getHeight());
    m_drawable->setVisible(true);
    const auto [dx, dy] = generateRandomDirection();
    m_moveable->setDirectionX(dx);
    m_moveable->setDirectionY(dy);
    m_moveable->setVelocity(initialVelocity());
}

void Ball::onDebug(bool debug) {
    Entity::onDebug(debug);
}

void Ball::reset() {
    setX(config::windowHalfWidth - m_collideable->getExtentX());
    setY(config::windowHalfHeight - m_collideable->getExtentY());

    const auto [x, y] = generateRandomDirection();
    m_moveable->setVelocity(0.f);
    m_moveable->setDirectionX(x);
    m_moveable->setDirectionY(y);

    m_drawable->setVisible(false);
    m_hitCount = 0;
    m_orangeBrickHit = false;
    m_redBrickHit = false;
}

void Ball::setWalls(std::initializer_list<std::reference_wrapper<Wall> > walls) {
    m_walls = walls;
}

constexpr float Ball::initialVelocity() {
    return static_cast<float>(config::windowHeight) / (config::windowHeight * 4.f);
}
