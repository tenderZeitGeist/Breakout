
#pragma once

#include <SDL2/SDL_rect.h>

#include <functional>

class Entity;
class RectShape;

class Shape {
public:
    virtual ~Shape() = default;
    explicit Shape(std::reference_wrapper<Entity> entity);
    [[nodiscard]] virtual SDL_Rect getBoundingBox() = 0;
    [[nodiscard]] virtual std::reference_wrapper<const Entity> getEntity() const;

protected:
    std::reference_wrapper<Entity> m_entity;
};

class CircleShape : public Shape {
public:
    explicit CircleShape(int radius, std::reference_wrapper<Entity> entity);
    [[nodiscard]] bool collidesWith(const CircleShape& other) const;
    [[nodiscard]] bool collidesWith(const RectShape& other) const;
    [[nodiscard]] SDL_Rect getBoundingBox() override;
private:
    int m_radius;
};

class RectShape : public Shape {
public:
    explicit RectShape(std::reference_wrapper<Entity> entity);
    [[nodiscard]] bool collidesWith(const CircleShape& other) const;
    [[nodiscard]] bool collidesWith(const RectShape& other) const;
    [[nodiscard]] SDL_Rect getBoundingBox() override;
};