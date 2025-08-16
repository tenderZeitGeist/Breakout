//
// Created by zeitgeist on 10.10.23.
//
#pragma once

#include "Collideable.h"
#include "Drawable.h"
#include "Moveable.h"

#include <SDL2/SDL.h>

#include <functional>

struct SDL_Renderer;

struct Vector2D {
    float x;
    float y;
};

class Entity {
public:
    struct Values {
        int x{-1};
        int y{-1};
        int width{0};
        int height{0};
        float velocity{0.f};
        SDL_Color color{0x00, 0x00, 0x00, 0x00};
    };

    using ComposeMask = uint8_t;
    enum Compose : ComposeMask {
        DRAWABLE = 1 << 0,
        MOVEABLE = 1 << 1,
        COLLIDEABLE = 1 << 2,
    };

    virtual ~Entity() = default;
    virtual void update(float delta);

    virtual void render(SDL_Renderer& renderer);
    virtual void init(Values v);
    virtual void reset();

    [[nodiscard]] int getX() const;
    [[nodiscard]] int getY() const;
    [[nodiscard]] int getWidth() const;
    [[nodiscard]] int getHeight() const;
    [[nodiscard]] const SDL_Rect& getRect() const;

    virtual void setX(int x);
    virtual void setY(int y);
    virtual void setWidth(int width);
    virtual void setHeight(int height);

    [[nodiscard]] virtual std::reference_wrapper<const Collideable> getCollideable() const;
    [[nodiscard]] virtual std::reference_wrapper<const Drawable> getDrawable() const;
    [[nodiscard]] virtual std::reference_wrapper<const Moveable> getMoveable() const;
    [[nodiscard]] virtual std::reference_wrapper<Collideable> getCollideable();
    [[nodiscard]] virtual std::reference_wrapper<Drawable> getDrawable();
    [[nodiscard]] virtual std::reference_wrapper<Moveable> getMoveable();

    virtual void onDebug(bool debug);

protected:
    explicit Entity(ComposeMask composeMask);
    Entity(Entity&&) = default;
    Entity& operator=(Entity&&) = default;

    SDL_Rect m_rect;

    Drawable m_drawable;
    Moveable m_moveable;
    Collideable m_collideable;
};

class Circle : public Entity {};
class Rect : public Entity {};
