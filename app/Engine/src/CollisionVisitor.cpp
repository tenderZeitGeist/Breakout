#include <Engine/CollisionVisitor.h>
#include <Engine/Shape.h>

bool CollisionVisitor::operator()(const CircleShape& lhs, const CircleShape& rhs) const {
    return lhs.collidesWith(rhs);
}

bool CollisionVisitor::operator()(const CircleShape& lhs, const RectShape& rhs) const {
    return lhs.collidesWith(rhs);
}

bool CollisionVisitor::operator()(const RectShape& lhs, const CircleShape& rhs) const {
    return lhs.collidesWith(rhs);
}

bool CollisionVisitor::operator()(const RectShape& lhs, const RectShape& rhs) const {
    return lhs.collidesWith(rhs);
}
