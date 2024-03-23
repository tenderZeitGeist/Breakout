//
// Created by zeitgeist on 10.10.23.
//
#pragma once

#include "Collideable.h"
#include "Drawable.h"
#include "Moveable.h"

#include <SDL2/SDL.h>

#include <memory>

struct SDL_Renderer;

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

    [[nodiscard]] int getX() const;
    [[nodiscard]] int getY() const;
    [[nodiscard]] int getWidth() const;
    [[nodiscard]] int getHeight() const;
    [[nodiscard]] const SDL_Rect& getRect() const;

    virtual void setX(int x);
    virtual void setY(int y);
    virtual void setWidth(int width);
    virtual void setHeight(int height);

    [[nodiscard]] virtual Collideable* getCollideable() const;
    [[nodiscard]] virtual Drawable* getDrawable() const;
    [[nodiscard]] virtual Moveable* getMoveable() const;

protected:
    explicit Entity(ComposeMask composeMask);
    Entity(Entity&&) = default;
    Entity& operator=(Entity&&) = default;

    SDL_Rect m_rect;

    std::unique_ptr<Collideable> m_collideable;
    std::unique_ptr<Moveable> m_moveable;
    std::unique_ptr<Drawable> m_drawable;
};
