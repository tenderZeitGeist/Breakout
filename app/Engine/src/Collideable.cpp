//
// Created by zeitgeist on 13.10.23.
//

#include "Engine/Collideable.h"
#include "Engine/CollisionVisitor.h"

#include <cmath>
#include <variant>

#include "Engine/Entity.h"

namespace {

int determineSide(int overlapX, int overlapY, bool fromRight, bool fromBottom) {
    if (overlapX <= 0 || overlapY <= 0) {
        return Side::NONE;
    }

    if (overlapX < overlapY) {
        return fromRight ? Side::RIGHT : LEFT;
    }

    return fromBottom ? Side::BOTTOM : Side::TOP;
}

}

Collideable::Collideable(std::reference_wrapper<Entity> entity)
    : m_entity(entity) {
}

bool operator==(const Collideable& lhs, const Collideable& rhs) {
    if (!lhs.isEnabled() || !rhs.isEnabled()) {
        return false;
    }
    return std::visit(CollisionVisitor{}, lhs.m_entity.get().getShape().get(), rhs.m_entity.get().getShape().get());
}

bool operator!=(const Collideable& lhs, const Collideable& rhs) {
    return !(lhs == rhs);
}

Side collides(const Entity& lhs, const Entity& rhs) {
    if (!lhs.getCollideable().get().isEnabled() || !rhs.getCollideable().get().isEnabled()) {
        return Side::NONE;
    }

    const auto deltaX = lhs.getCenterX() - rhs.getCenterX();
    const auto deltaY = lhs.getCenterY() - rhs.getCenterY();
    const auto sumOfExtentX = lhs.getExtentX() + rhs.getExtentX();
    const auto sumOfExtentY = lhs.getExtentY() + rhs.getExtentY();
    const auto overlapX = sumOfExtentX - std::abs(deltaX);
    const auto overlapY = sumOfExtentY - std::abs(deltaY);

    return static_cast<Side>(determineSide(overlapX, overlapY, deltaX > 0, deltaY > 0));
}

bool Collideable::isEnabled() const {
    return m_enabled;
}

void Collideable::setEnabled(bool enabled) {
    m_enabled = enabled;
}
