#include <Engine/Collidable.h>
#include <Game/Paddle.h>

Paddle::Paddle()
    : Entity(DRAWABLE | MOVEABLE | COLLIDABLE) {
}

void Paddle::update(float dt) {
    const auto previousX = getX();
    m_moveable.move(dt);
    for (const auto wallRef : m_walls) {
        auto& wall = wallRef.get();
        if (wall.getCollidable() == getCollidable()) {
            setX(previousX);
            return;
        }
    }
}

void Paddle::init(Entity::Values v) {
    Entity::init(v);
    setDefaultPosition(v.x, v.y);
    m_originalWidth = getWidth();
}

void Paddle::reset() {
    setX(m_defaultX);
    setY(m_defaultY);
    if (m_originalWidth != getWidth()) {
        setWidth(m_originalWidth);
    }
    m_drawable.setVisible(true);
}

void Paddle::setWalls(std::initializer_list<std::reference_wrapper<Wall>> walls) {
    m_walls = walls;
}

void Paddle::setDefaultPosition(int x, int y) {
    m_defaultX = x;
    m_defaultY = y;
}
