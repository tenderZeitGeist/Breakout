//
// Created by zeitgeist on 13.10.23.
//

#include "Engine/Collidable.h"
#include "Engine/CollisionVisitor.h"

#include <algorithm>
#include <cmath>
#include <variant>

#include "Engine/Entity.h"

Collidable::Collidable(std::reference_wrapper<Entity> entity)
    : m_entity(entity) {
}

bool operator==(const Collidable& lhs, const Collidable& rhs) {
    if (!lhs.isEnabled() || !rhs.isEnabled()) {
        return false;
    }
    return std::visit(CollisionVisitor{}, lhs.m_entity.get().getShape().get(), rhs.m_entity.get().getShape().get());
}

bool operator!=(const Collidable& lhs, const Collidable& rhs) {
    return !(lhs == rhs);
}

Side determineSide(const Collidable& lhs, const Collidable& rhs) {
    if (!lhs.isEnabled() || !rhs.isEnabled()) {
        return Side::NONE;
    }

    const auto& lhsEntity = lhs.m_entity.get();
    const auto& rhsEntity = rhs.m_entity.get();
    const auto distanceLeft = lhsEntity.getCenterX() - rhsEntity.getX();
    const auto distanceRight= rhsEntity.getX() + rhsEntity.getWidth() - lhsEntity.getCenterX();
    const auto distanceTop= lhsEntity.getCenterY() - rhsEntity.getY();
    const auto distanceBottom= rhsEntity.getY() + rhsEntity.getHeight() - lhsEntity.getCenterY();
    const auto min = std::min({distanceLeft, distanceRight, distanceTop, distanceBottom});

    if (min == distanceLeft) {
        return Side::LEFT; }
    if (min == distanceRight) {
        return Side::RIGHT;
    }
    if (min == distanceTop) {
        return Side::TOP;
    }
    return Side::BOTTOM;
}

bool Collidable::isEnabled() const {
    return m_enabled;
}

void Collidable::setEnabled(bool enabled) {
    m_enabled = enabled;
}
