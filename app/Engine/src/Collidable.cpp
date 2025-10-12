#include <Engine/Collidable.h>
#include <Engine/CollisionVisitor.h>
#include <Engine/Entity.h>

#include <variant>

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

bool Collidable::isEnabled() const {
    return m_enabled;
}

void Collidable::setEnabled(bool enabled) {
    m_enabled = enabled;
}
