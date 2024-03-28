//
// Created by zeitgeist on 12.10.23.
//

#include "Engine/Drawable.h"
#include "Engine/Entity.h"

#include <SDL2/SDL_render.h>

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
}

bool Drawable::isVisible() const {
    return m_visible;
}

const SDL_Color& Drawable::getColor() const {
    return m_color;
}

Drawable::Shape Drawable::getShape() const {
    return m_shape;
}

void Drawable::setVisible(bool visible) {
    m_visible = visible;
}

void Drawable::setColor(const SDL_Color& color) {
    m_color = color;
}

void Drawable::setShape(Shape shape) {
    m_shape = shape;
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

    while (x >= y) {
        for(auto [tx, ty] : std::initializer_list<std::pair<int,int>>{
            {centerX + x, centerY - y},
            {centerX + x, centerY + y},
            {centerX - x, centerY - y},
            {centerX - x, centerY + y},
            {centerX + y, centerY - x},
            {centerX + y, centerY + x},
            {centerX - y, centerY - x},
            {centerX - y, centerY + x}
        }) {
            SDL_RenderDrawPoint(&renderer, tx, ty);
        }

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
