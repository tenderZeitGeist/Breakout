//
// Created by zeitgeist on 10.10.23.
//

#include "Engine/Entity.h"

Entity::Entity(ComposeMask composeMask)
    : m_rect({0, 0, 0, 0})
    , m_drawable(*this)
    , m_moveable(*this)
    , m_collideable(*this) {
    if (composeMask & DRAWABLE) {
        m_drawable.setActive(true);
    }
    if (composeMask & MOVEABLE) {
        m_moveable.setActive(true);
    }
    if (composeMask & COLLIDEABLE) {
        m_collideable.setActive(true);
    }
}

void Entity::update(float delta) {

}

void Entity::init(Entity::Values v) {
    setX(v.x);
    setY(v.y);
    setWidth(v.width);
    setHeight(v.height);
    if (m_drawable.isActive()) {
        m_drawable.setColor(v.color);
    }
    if (m_moveable.isActive()) {
        m_moveable.setVelocity(v.velocity);
    }
}

void Entity::reset() {

}

void Entity::render(SDL_Renderer& renderer) {
    if (!m_drawable.isActive() || !m_drawable.isVisible()) {
        return;
    }
    m_drawable.render(renderer);
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
    if (m_collideable.isActive()) {
        const auto centerX = m_collideable.getCenterX();
        const auto deltaX = getX() - x;
        m_collideable.setCenterX(centerX - deltaX);
    }
    m_rect.x = static_cast<Sint16>(x);
}

void Entity::setY(int y) {
    if (m_collideable.isActive()) {
        const auto centerY = m_collideable.getCenterY();
        const auto deltaY = getY() - y;
        m_collideable.setCenterY(centerY - deltaY);
    }
    m_rect.y = static_cast<Sint16>(y);
}

void Entity::setWidth(int width) {
    if (m_collideable.isActive()) {
        const auto extentX = width / 2;
        m_collideable.setExtentX(extentX);
        m_collideable.setCenterX(getX() + extentX);
    }
    m_rect.w = static_cast<Uint16>(width);
}

void Entity::setHeight(int height) {
    if (m_collideable.isActive()) {
        const auto extentY = height / 2;
        m_collideable.setExtentY(extentY);
        m_collideable.setCenterY(getY() + extentY);
    }
    m_rect.h = static_cast<Uint16>(height);
}

std::reference_wrapper<const Collideable> Entity::getCollideable() const {
    return std::cref(m_collideable);
}

std::reference_wrapper<const Drawable> Entity::getDrawable() const {
    return std::cref(m_drawable);
}

std::reference_wrapper<const Moveable> Entity::getMoveable() const {
    return std::cref(m_moveable);
}

std::reference_wrapper<Collideable> Entity::getCollideable() {
    return std::ref(m_collideable);
}

std::reference_wrapper<Drawable> Entity::getDrawable() {
    return std::ref(m_drawable);
}

std::reference_wrapper<Moveable> Entity::getMoveable() {
    return std::ref(m_moveable);
}

void Entity::onDebug(bool debug) {
    // Base case may be ignored.
}
