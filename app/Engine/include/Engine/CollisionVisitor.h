#pragma once

class CircleShape;
class RectShape;

struct CollisionVisitor {
    [[nodiscard]] bool operator()(const CircleShape& lhs, const CircleShape& rhs) const;
    [[nodiscard]] bool operator()(const CircleShape& lhs, const RectShape& rhs) const;
    [[nodiscard]] bool operator()(const RectShape& lhs, const CircleShape& rhs) const;
    [[nodiscard]] bool operator()(const RectShape& lhs, const RectShape& rhs) const;
};

