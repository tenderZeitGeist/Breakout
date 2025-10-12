#include <Engine/Entity.h>
#include <Engine/Shape.h>

#include <cassert>

Entity::Entity(ComposeMask composeMask)
    : m_rect({0, 0, 0, 0})
    , m_drawable(*this)
    , m_moveable(*this)
    , m_collidable(*this)
    , m_shapeVariant{RectShape{*this}} {
    if (composeMask & DRAWABLE) {
        m_drawable.setActive(true);
    }
    if (composeMask & MOVEABLE) {
        m_moveable.setActive(true);
    }
    if (composeMask & COLLIDABLE) {
        m_collidable.setActive(true);
    }
}

void Entity::update(float) {
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

    switch (v.shape) {
        case ShapeType::RECT:
            break;
        case ShapeType::CIRCLE:
            assert(getWidth() == getHeight() && "Unequal width and height.");
            m_shapeVariant = CircleShape{getWidth(), *this};
            break;
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

int Entity::getCenterX() const {
    return m_centerX;
}

int Entity::getCenterY() const {
    return m_centerY;
}

int Entity::getExtentX() const {
    return m_extentX;
}

int Entity::getExtentY() const {
    return m_extentY;
}

const SDL_Rect& Entity::getRect() const {
    return m_rect;
}

void Entity::setX(int x) {
    const auto deltaX = getX() - x;
    setCenterX(getCenterX() - deltaX);
    m_rect.x = static_cast<Sint16>(x);
}

void Entity::setY(int y) {
    const auto deltaY = getY() - y;
    setCenterY(getCenterY() - deltaY);
    m_rect.y = static_cast<Sint16>(y);
}

void Entity::setWidth(int width) {
    const auto extent = width / 2;
    setExtentX(extent);
    setCenterX(getX() + extent);
    m_rect.w = static_cast<Uint16>(width);
}

void Entity::setHeight(int height) {
    const auto extent = height / 2;
    setExtentY(extent);
    setCenterY(getY() + extent);
    m_rect.h = static_cast<Uint16>(height);
}

void Entity::setCenterX(int centerX) {
    m_centerX = centerX;
}

void Entity::setCenterY(int centerY) {
    m_centerY = centerY;
}

void Entity::setExtentX(int extentX) {
    m_extentX = extentX;
}

void Entity::setExtentY(int extentY) {
    m_extentY = extentY;
}

std::reference_wrapper<const Collidable> Entity::getCollidable() const {
    return std::cref(m_collidable);
}

std::reference_wrapper<const Drawable> Entity::getDrawable() const {
    return std::cref(m_drawable);
}

std::reference_wrapper<const Moveable> Entity::getMoveable() const {
    return std::cref(m_moveable);
}

std::reference_wrapper<const ShapeVariant> Entity::getShape() const {
    return std::cref(m_shapeVariant);
}

std::reference_wrapper<Collidable> Entity::getCollidable() {
    return std::ref(m_collidable);
}

std::reference_wrapper<Drawable> Entity::getDrawable() {
    return std::ref(m_drawable);
}

std::reference_wrapper<Moveable> Entity::getMoveable() {
    return std::ref(m_moveable);
}

std::reference_wrapper<ShapeVariant> Entity::getShape() {
    return std::ref(m_shapeVariant);
}

void Entity::onDebug(bool) {
    // Base case may be ignored.
}
