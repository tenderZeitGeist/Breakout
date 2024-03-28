//
// Created by zeitgeist on 27.03.24.
//

#include "Game/Ball.h"

#include <Engine/Configuration.h>

#include <cassert>
#include <random>

struct Vector2D {
    float x;
    float y;
};

namespace {
    Vector2D normalize(const Vector2D vector) {
        const auto x = vector.x;
        const auto y = vector.y;
        const auto length = std::sqrt(x * x + y * y);
        return {length / x, length / y};
    }

    Vector2D generateRandomDirection() {
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution distribution(1, 3);

        const Vector2D direction = [value = distribution(rng)]() -> Vector2D {
            switch (value) {
                case 1:
                    return {0.f, 1.f};
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
        return normalize(direction);
    }
}

Ball::Ball()
: Entity(COLLIDEABLE | DRAWABLE | MOVEABLE, Drawable::Shape::CIRCLE) {
}

void Ball::update(float delta) {
    m_moveable->move(delta);
}

void Ball::init(Values v) {
    Entity::init(v);
    assert(getWidth() == getHeight());
    m_drawable->setVisible(true);
    const auto [dx, dy] = generateRandomDirection();
    m_moveable->setDirectionX(dx);
    m_moveable->setDirectionY(dy);
    //m_moveable->setVelocity(0.06f);
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
