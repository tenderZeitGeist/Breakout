
#include <Engine/Entity.h>
#include <Engine/Shape.h>

Shape::Shape(std::reference_wrapper<Entity> entity)
    : m_entity(entity) {
}

std::reference_wrapper<const Entity> Shape::getEntity() const {
    return m_entity;
}

CircleShape::CircleShape(int radius, std::reference_wrapper<Entity> entity)
    : Shape(entity)
    , m_radius(radius) {
}

bool CircleShape::collidesWith(const CircleShape& other) const {
    const auto dx = std::abs(m_entity.get().getCollideable().get().getCenterX()
                             - other.m_entity.get().getCollideable().get().getCenterX());
    const auto dy = std::abs(m_entity.get().getCollideable().get().getCenterY()
                             - other.m_entity.get().getCollideable().get().getCenterY());
    const auto distanceSquared = dx * dx + dy * dy;
    const auto sumOfRadius = m_radius + other.m_radius;
    return distanceSquared <= sumOfRadius;
}

bool CircleShape::collidesWith(const RectShape& other) const {
    const auto centerX = m_entity.get().getCollideable().get().getCenterX();
    const auto centerY = m_entity.get().getCollideable().get().getCenterY();
    const auto& rectEntity = other.getEntity().get();
    const auto edgeX = std::max(rectEntity.getX(), std::min(centerX, rectEntity.getX() + rectEntity.getWidth()));
    const auto edgeY = std::max(rectEntity.getY(), std::min(centerY, rectEntity.getY() + rectEntity.getHeight()));
    const auto dx = centerX - edgeX;
    const auto dy = centerY - edgeY;
    const auto distanceSquared = dx * dx + dy * dy;
    const auto radiusSquared = m_radius * m_radius;
    return distanceSquared <= radiusSquared;
}

SDL_Rect CircleShape::getBoundingBox() {
    return {m_entity.get().getX() - m_radius, m_entity.get().getY() - m_radius, m_radius * 2, m_radius * 2};
}

RectShape::RectShape(std::reference_wrapper<Entity> entity)
    : Shape(entity) {
}

bool RectShape::collidesWith(const CircleShape& other) const {
    return other.collidesWith(*this);
}

bool RectShape::collidesWith(const RectShape& other) const {
    const auto& lhs = m_entity.get();
    const auto& rhs = other.getEntity().get();
    return lhs.getX() + lhs.getWidth() >= rhs.getX()
            && lhs.getX() <= rhs.getX() + rhs.getWidth()
            && lhs.getY() + lhs.getHeight() >= rhs.getY()
            && lhs.getY() <= rhs.getY() + rhs.getHeight();
}

SDL_Rect RectShape::getBoundingBox() {
    return m_entity.get().getRect();
}
