//
// Created by zeitgeist on 27.03.24.
//

#include <Game/Ball.h>
#include <Game/Brick.h>
#include <Game/GameEvent.h>
#include <Game/Paddle.h>
#include <Game/Wall.h>

#include <Engine/Configuration.h>
#include <Engine/EventManager.h>

#include <algorithm>
#include <cassert>
#include <cmath>
#include <random>
#include <ranges>

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

enum Side : std::uint8_t {
    NONE = 0,
    LEFT = 1 << 0,
    RIGHT = 1 << 1,
    TOP = 1 << 2,
    BOTTOM = 1 << 3,
};

Side determineSide(const Ball& ball, const Brick& brick) {
    const auto distanceLeft = ball.getCenterX() - brick.getX();
    const auto distanceRight = brick.getX() + brick.getWidth() - ball.getCenterX();
    const auto distanceTop = ball.getCenterY() - brick.getY();
    const auto distanceBottom = brick.getY() + brick.getHeight() - ball.getCenterY();
    const auto min = std::min({distanceLeft, distanceRight, distanceTop, distanceBottom});

    if (min == distanceLeft) {
        return Side::LEFT;
    }
    if (min == distanceRight) {
        return Side::RIGHT;
    }
    if (min == distanceTop) {
        return Side::TOP;
    }
    return Side::BOTTOM;
}

}

Ball::Ball(std::reference_wrapper<Paddle> paddle, std::shared_ptr<events::EventManager> eventManager)
    : Entity(COLLIDABLE | DRAWABLE | MOVEABLE)
    , m_paddle(paddle)
    , m_eventManager(std::move(eventManager)) {
    assert(m_eventManager);
}

void Ball::update(float delta) {
    m_previousX = getX();
    m_previousY = getY();
    m_moveable.move(delta);

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
    reset();
}

void Ball::onDebug(bool debug) {
    m_drawable.showVector(debug);
}

void Ball::reset() {
    setX(config::windowHalfWidth - getExtentX());
    setY(config::windowHalfHeight - getExtentY());
    m_moveable.setDirection(generateRandomDirection());
    m_moveable.setVelocity(initialVelocity());
    m_drawable.setVisible(true);
}

void Ball::setWalls(std::vector<std::reference_wrapper<Wall>> walls) {
    m_walls = std::move(walls);
}

void Ball::setBricks(std::vector<std::reference_wrapper<Brick>> bricks) {
    m_bricks = std::move(bricks);
}

constexpr float Ball::initialVelocity() {
    return static_cast<float>(config::windowHeight) / (config::windowHeight * 2.f);
}

bool Ball::outOfBounds() const {
    const auto centerX = getCenterX();
    const auto centerY = getCenterY();
    const auto x = centerX < 0 || centerX > config::windowWidth;
    const auto y = centerY < 0 || centerY > config::windowHeight;
    return x || y;
}

bool Ball::collidedWithWall() {
    const auto iter = std::ranges::find_if(m_walls, [&collidable = m_collidable](const auto wallRef) {
        return wallRef.get().getCollidable() == collidable;
    });

    if (iter == m_walls.end()) {
        return false;
    }

    resetToPreviousPosition();
    const auto wallNormals = iter->get().getNormals();
    const auto isSideWall = wallNormals.x != 0.f;
    if (isSideWall) {
        m_moveable.setDirectionX(-m_moveable.getDirectionX());
    } else {
        m_moveable.setDirectionY(-m_moveable.getDirectionY());
    }
    return true;
}

bool Ball::collidedWithPaddle() {
    const auto& paddle = m_paddle.get();
    if (m_collidable != paddle.getCollidable()) {
        return false;
    }

    setX(m_previousX);
    setY(paddle.getY() - getExtentY() - paddle.getExtentY());

    const auto distanceX = static_cast<float>(getCenterX() - paddle.getCenterX());
    const auto dx = distanceX / static_cast<float>(paddle.getExtentX());
    const auto dy = -m_moveable.getDirectionY();
    const auto newDirection = normalize(Vector2D{dx, dy});
    m_moveable.setDirection(newDirection);

    return true;
}


bool Ball::collidedWithBrick() {
    const auto iter = std::ranges::find_if(m_bricks, [&collidable = m_collidable](const auto brickRef) {
        return collidable == brickRef.get().getCollidable();
    });

    if (iter == m_bricks.end()) {
        return false;
    }

    resetToPreviousPosition();
    const auto brickRef = *iter;
    const auto side = determineSide(*this, brickRef);
    m_moveable.setDirectionX(m_moveable.getDirectionX() * static_cast<float>(1 - 2 * (side == LEFT || side == RIGHT)));
    m_moveable.setDirectionY(m_moveable.getDirectionY() * static_cast<float>(1 - 2 * (side == TOP || side == BOTTOM)));
    m_eventManager->notify(events::BrickDestroyed{brickRef});
    return true;
}

void Ball::resetToPreviousPosition() {
    setX(m_previousX);
    setY(m_previousY);
}
