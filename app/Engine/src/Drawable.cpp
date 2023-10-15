//
// Created by zeitgeist on 12.10.23.
//

#include "../Drawable.h"
#include "../Entity.h"

#include <SDL2/SDL_render.h>

Drawable::Drawable(Entity& entity)
: m_entity(entity) {

}

void Drawable::render(SDL_Renderer& renderer) {
    const auto color = getColor();
    SDL_SetRenderDrawColor(&renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(&renderer, &m_entity.getRect());
}

bool Drawable::isVisible() const {
    return false;
}

const SDL_Color& Drawable::getColor() const {
    return m_color;
}

void Drawable::setVisible(bool visible) {

}

void Drawable::setColor(const SDL_Color& color) {
    m_color = color;
}
