//
// Created by zeitgeist on 11.10.23.
//

#pragma once

#include <Engine/Component.h>

#include <SDL2/SDL.h>

class Entity;
class Game;
struct SDL_Renderer;

class Drawable : public Component {
public:
    explicit Drawable(Entity& entity);

    ~Drawable() = default;
    void render(SDL_Renderer& renderer) const;

    [[nodiscard]] bool isVisible() const;
    [[nodiscard]] const SDL_Color& getColor() const;

    void setVisible(bool visible);
    void setColor(const SDL_Color& color);
    void showVector(bool debug);

private:
    void drawRect(SDL_Renderer& renderer) const;
    void drawCircle(SDL_Renderer& renderer) const;

    Entity& m_entity;
    SDL_Color m_color{};
    bool m_visible{true};
    bool m_debug{false};
};