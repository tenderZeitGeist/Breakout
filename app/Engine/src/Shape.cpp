
#include <Engine/Entity.h>
#include <Engine/Shape.h>

#include <algorithm>

CircleShape::CircleShape(int radius, std::reference_wrapper<Entity> entity)
    : Shape(entity)
    , m_radius(radius) {
}

bool CircleShape::collidesWith(const CircleShape& other) const {
    const auto dx = m_entity.get().getCenterX() - other.m_entity.get().getCenterX();
    const auto dy = m_entity.get().getCenterY() - other.m_entity.get().getCenterY();
    const auto distanceSquared = dx * dx + dy * dy;
    const auto sumOfRadii = m_radius + other.m_radius;
    const auto sumOfRadiiSquared = sumOfRadii * sumOfRadii;
    return distanceSquared <= sumOfRadiiSquared;
}

bool CircleShape::collidesWith(const RectShape& other) const {
    const auto centerX = m_entity.get().getCenterX();
    const auto centerY = m_entity.get().getCenterY();
    const auto& rectEntity = other.getEntity().get();
    const auto edgeX = std::clamp(centerX, rectEntity.getX(), rectEntity.getX() + rectEntity.getWidth());
    const auto edgeY = std::clamp(centerY, rectEntity.getY(), rectEntity.getY() + rectEntity.getHeight());
    const auto dx = centerX - edgeX;
    const auto dy = centerY - edgeY;
    const auto distanceSquared = dx * dx + dy * dy;
    const auto radiusSquared = m_radius * m_radius;
    return distanceSquared <= radiusSquared;
}

const SDL_Rect& CircleShape::getBoundingBox() const {
    return m_entity.get().getRect();
}

int CircleShape::getRadius() const {
    return m_radius;
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

const SDL_Rect& RectShape::getBoundingBox() const {
    return m_entity.get().getRect();
}
