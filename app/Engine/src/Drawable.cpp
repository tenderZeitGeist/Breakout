//
// Created by zeitgeist on 12.10.23.
//

#include "Engine/Drawable.h"
#include "Engine/Entity.h"

#include <SDL2/SDL_render.h>

#include <array>

#include "Engine/Configuration.h"

Drawable::Drawable(Entity& entity, Shape shape)
: m_entity(entity)
, m_shape(shape) {
}

void Drawable::render(SDL_Renderer& renderer) const {
    const auto color = getColor();
    SDL_SetRenderDrawColor(&renderer, color.r, color.g, color.b, color.a);
    switch (m_shape) {
        case Shape::RECT:
            drawRect(renderer);
            break;
        case Shape::CIRCLE:
            drawCircle(renderer);
            break;
    }

    if(m_debug) {
        const auto direction = m_entity.getMoveable()->currentDirection();
        constexpr auto debugColor = config::kDebugColor;
        const auto centerX = m_entity.getX() + m_entity.getWidth() / 2;
        const auto centerY = m_entity.getY() + m_entity.getHeight() / 2;
        const auto directionX = centerX + static_cast<int>(static_cast<float>(m_entity.getWidth()) * std::cos(direction) * 2);
        const auto directionY = centerY + static_cast<int>(static_cast<float>(m_entity.getHeight()) * std::sin(direction) * 2);
        SDL_SetRenderDrawColor(&renderer, debugColor.r, debugColor.g, debugColor.b, debugColor.a);
        SDL_RenderDrawLine(&renderer, centerX, centerY, directionX, directionY);
    }
}

bool Drawable::isVisible() const {
    return m_visible;
}

const SDL_Color& Drawable::getColor() const {
    return m_color;
}

void Drawable::setVisible(bool visible) {
    m_visible = visible;
}

void Drawable::setColor(const SDL_Color& color) {
    m_color = color;
}

void Drawable::showVector(bool debug) {
    m_debug = debug;
}

void Drawable::drawRect(SDL_Renderer& renderer) const {
    SDL_RenderFillRect(&renderer, &m_entity.getRect());
}

void Drawable::drawCircle(SDL_Renderer& renderer) const {
    const int diameter = m_entity.getWidth();
    const int radius = diameter / 2;
    const auto centerX = m_entity.getX() + radius;
    const auto centerY = m_entity.getY() + radius;

    int x = radius - 1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int error = dx - diameter;

    static std::array<SDL_Point, 8> points;

    while (x >= y) {
        points = {
            centerX + x, centerY - y,
            centerX + x, centerY + y,
            centerX - x, centerY - y,
            centerX - x, centerY + y,
            centerX + y, centerY - x,
            centerX + y, centerY + x,
            centerX - y, centerY - x,
            centerX - y, centerY + x
        };
            SDL_RenderDrawLines(&renderer, points.data(), points.size());

        if(error <= 0) {
            ++y;
            error += dy;
            dy += 2;
        }
        if(error > 0) {
            --x;
            dx += 2;
            error += dx - diameter;
        }
    }
}
