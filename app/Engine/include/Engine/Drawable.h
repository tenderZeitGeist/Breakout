//
// Created by zeitgeist on 11.10.23.
//

#pragma once

#include <SDL2/SDL.h>

class Entity;
class Game;
struct SDL_Renderer;

class Drawable {
public:
    explicit Drawable(Entity& entity);

    ~Drawable() = default;
    void render(SDL_Renderer& renderer);

    [[nodiscard]] bool isVisible() const;
    [[nodiscard]] const SDL_Color& getColor() const;

    void setVisible(bool visible);
    void setColor(const SDL_Color& color);

protected:
    Entity& m_entity;
    SDL_Color m_color;
    bool m_visible{false};
};