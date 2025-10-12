#pragma once

#include <SDL2/SDL_rect.h>

#include <functional>
#include <variant>

class Entity;
class RectShape;
class CircleShape;

using ShapeVariant = std::variant<RectShape, CircleShape>;
enum class ShapeType { RECT, CIRCLE };

template<typename Derived>
class Shape {
public:

    explicit Shape(std::reference_wrapper<Entity> entity)
        : m_entity(entity) {
    }

    [[nodiscard]] const SDL_Rect& getBoundingBox() const {
        return static_cast<const Derived*>(this)->getBoundingBox();
    }

    [[nodiscard]] std::reference_wrapper<const Entity> getEntity() const {
        return m_entity;
    }

protected:
    std::reference_wrapper<Entity> m_entity;
};

class CircleShape : public Shape<CircleShape> {
public:
    explicit CircleShape(int radius, std::reference_wrapper<Entity> entity);
    [[nodiscard]] bool collidesWith(const CircleShape& other) const;
    [[nodiscard]] bool collidesWith(const RectShape& other) const;
    [[nodiscard]] const SDL_Rect& getBoundingBox() const;
    [[nodiscard]] int getRadius() const;

private:
    int m_radius;
};

class RectShape : public Shape<RectShape> {
public:
    explicit RectShape(std::reference_wrapper<Entity> entity);
    [[nodiscard]] bool collidesWith(const CircleShape& other) const;
    [[nodiscard]] bool collidesWith(const RectShape& other) const;
    [[nodiscard]] const SDL_Rect& getBoundingBox() const;
};
