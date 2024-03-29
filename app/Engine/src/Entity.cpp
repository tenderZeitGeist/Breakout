//
// Created by zeitgeist on 10.10.23.
//

#include "Engine/Entity.h"

Entity::Entity(ComposeMask composeMask, Drawable::Shape shape)
    : m_rect({0, 0, 0, 0}) {
    auto& self = *this;
    if (composeMask & DRAWABLE) {
        m_drawable = std::make_unique<Drawable>(self, shape);
    }
    if (composeMask & MOVEABLE) {
        m_moveable = std::make_unique<Moveable>(self);
    }
    if (composeMask & COLLIDEABLE) {
        m_collideable = std::make_unique<Collideable>(self);
    }
}

void Entity::update(float delta) {

}

void Entity::init(Entity::Values v) {
    setX(v.x);
    setY(v.y);
    setWidth(v.width);
    setHeight(v.height);
    if (m_drawable) {
        m_drawable->setColor(v.color);
    }
    if (m_moveable) {
        m_moveable->setVelocity(v.velocity);
    }
}

void Entity::render(SDL_Renderer& renderer) {
    if (m_drawable && m_drawable->isVisible()) {
        m_drawable->render(renderer);
    }
}

int Entity::getX() const {
    return m_rect.x;
}

int Entity::getY() const {
    return m_rect.y;
}

int Entity::getWidth() const {
    return m_rect.w;
}

int Entity::getHeight() const {
    return m_rect.h;
}

const SDL_Rect& Entity::getRect() const {
    return m_rect;
}

void Entity::setX(int x) {
    if (m_collideable) {
        const auto centerX = m_collideable->getCenterX();
        const auto deltaX = getX() - x;
        m_collideable->setCenterX(centerX - deltaX);
    }
    m_rect.x = static_cast<Sint16>(x);
}

void Entity::setY(int y) {
    if (m_collideable) {
        const auto centerY = m_collideable->getCenterY();
        const auto deltaY = getY() - y;
        m_collideable->setCenterY(centerY - deltaY);
    }
    m_rect.y = static_cast<Sint16>(y);
}

void Entity::setWidth(int width) {
    if (m_collideable) {
        const auto extentX = width / 2;
        m_collideable->setExtentX(extentX);
        m_collideable->setCenterX(getX() + extentX);
    }
    m_rect.w = static_cast<Uint16>(width);
}

void Entity::setHeight(int height) {
    if (m_collideable) {
        const auto extentY = height / 2;
        m_collideable->setExtentY(extentY);
        m_collideable->setCenterY(getY() + extentY);
    }
    m_rect.h = static_cast<Uint16>(height);
}

Collideable* Entity::getCollideable() const {
    return m_collideable.get();
}

Drawable* Entity::getDrawable() const {
    return m_drawable.get();
}

Moveable* Entity::getMoveable() const {
    return m_moveable.get();
}

void Entity::onDebug(bool debug) {
    // Base case may be ignored.
}
