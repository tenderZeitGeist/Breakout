//
// Created by zeitgeist on 27.03.24.
//

#include <Game/Ball.h>
#include <Game/Brick.h>
#include <Game/Wall.h>
#include <Game/Paddle.h>
#include <Game/GameEvent.h>

#include <Engine/Configuration.h>
#include <Engine/EventManager.h>

#include <algorithm>
#include <cassert>
#include <random>
#include <cmath>

namespace {
    float magnitude(float x, float y) {
        return std::sqrt(x * x + y * y);
    }

    float magnitude(Vector2D v) {
        return magnitude(v.x, v.y);
    }

    Vector2D normalize(const Vector2D vector) {
        const auto length = magnitude(vector);
        return {vector.x / length, vector.y / length};
    }

    Vector2D generateRandomDirection() {
        static std::random_device rd;
        static std::mt19937 rng(rd());
        static std::uniform_int_distribution distribution(1, 3);

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

    Vector2D reflection(Vector2D v1, Vector2D v2) {
        const float dotProduct = v1.x * v2.x + v1.y * v2.y;
        // R = v1 - 2(v1 * v2)v2
        return {
            v1.x - 2 * dotProduct * v2.x,
            v2.y - 2 * dotProduct * v2.y
        };
    }

    Vector2D calculateDirection(Vector2D v1, Vector2D v2) {
        return normalize(reflection(v1, v2));
    }
}

Ball::Ball(std::reference_wrapper<Paddle> paddle, std::shared_ptr<events::EventManager> eventManager)
    : Entity(COLLIDEABLE | DRAWABLE | MOVEABLE, Drawable::Shape::CIRCLE)
    , m_paddle(paddle)
    , m_eventManager(std::move(eventManager)) {
    assert(m_eventManager);
}

void Ball::update(float delta) {
    m_previousX = getX();
    m_previousY = getY();
    m_moveable->move(delta);

    if (outOfBounds()) {
        m_eventManager->notify(events::BallOutOfBounds());
        return;
    }

    if (collidedWithWall() || collidedWithPaddle() || collidedWithBrick()) {
        return;
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
    m_drawable->showVector(debug);
}

void Ball::reset() {
    setX(config::windowHalfWidth - m_collideable->getExtentX());
    setY(config::windowHalfHeight - m_collideable->getExtentY());

    const auto [x, y] = generateRandomDirection();
    m_moveable->setDirection({x, y});
    m_drawable->setVisible(true);
}

void Ball::setWalls(std::vector<std::reference_wrapper<Wall>> walls) {
    m_walls = std::move(walls);
}

void Ball::setBricks(std::vector<std::reference_wrapper<Brick>> bricks) {
    m_bricks = std::move(bricks);
}

constexpr float Ball::initialVelocity() {
    return static_cast<float>(config::windowHeight) / (config::windowHeight * 3.f);
}

bool Ball::outOfBounds() const {
    const auto collideable = getCollideable();
    const auto centerX = collideable->getCenterX();
    const auto centerY = collideable->getCenterY();
    const auto x = centerX < 0 || centerX > config::windowWidth;
    const auto y = centerY < 0 || centerY > config::windowHeight;
    return x || y;
}

bool Ball::collidedWithWall() {
    // TODO: Refactor logic to use ranges.
    for (auto wallRef: m_walls) {
        const auto& wall = wallRef.get();
        if (*wall.getCollideable() == *m_collideable) {
            resetToPreviousPosition();
            const auto wallNormals = wall.getNormals();
            const auto isSideWall = wallNormals.x != 0.f;
            if (isSideWall) {
                m_moveable->setDirectionX(-m_moveable->getDirectionX());
            } else {
                m_moveable->setDirectionY(-m_moveable->getDirectionY());
            }
            return true;
        }
    }
    return false;
}

bool Ball::collidedWithPaddle() {
    const auto& paddle = m_paddle.get();
    if (*m_collideable != *paddle.getCollideable()) {
        return false;
    }
    setY(paddle.getY() - getHeight());

    const auto distanceX = static_cast<float>(m_collideable->getCenterX() - paddle.getCollideable()->getCenterX());
    const auto dx = distanceX / static_cast<float>(paddle.getCollideable()->getExtentX());
    const auto paddleNormal = normalize({dx, -1.0f});
    const auto oldDirection = m_moveable->getDirection();
    const auto newDirection = calculateDirection(oldDirection, paddleNormal);
    m_moveable->setDirection(newDirection);

    return true;
}


bool Ball::collidedWithBrick() {
    // TODO: Refactor logic to use ranges.
    for (auto brickRef: m_bricks) {
        const auto& brick = brickRef.get();
        if (*m_collideable == *brick.getCollideable()) {
            resetToPreviousPosition();
            m_moveable->setDirectionY(-m_moveable->getDirectionY());
            m_eventManager->notify(events::BrickDestroyed{brick});
            return true;
        }
    }
    return false;
}

void Ball::resetToPreviousPosition() {
    setX(m_previousX);
    setY(m_previousY);
}
