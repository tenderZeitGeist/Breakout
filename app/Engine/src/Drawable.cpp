#include <Engine/Configuration.h>
#include <Engine/Drawable.h>
#include <Engine/Entity.h>
#include <Engine/RenderVisitor.h>

#include <SDL2/SDL_render.h>

#include <variant>

Drawable::Drawable(std::reference_wrapper<Entity> entity)
: m_entity(entity) {
}

void Drawable::render(SDL_Renderer& renderer) const {
    const auto color = getColor();
    SDL_SetRenderDrawColor(&renderer, color.r, color.g, color.b, color.a);
    std::visit(RenderVisitor{renderer}, m_entity.get().getShape().get());

    if(!m_debug) {
        return;
    }

    const auto& entity = m_entity.get();
    const auto direction = entity.getMoveable().get().currentDirection();
    constexpr auto debugColor = config::kDebugColor;
    const auto centerX = entity.getX() + entity.getWidth() / 2;
    const auto centerY = entity.getY() + entity.getHeight() / 2;
    const auto directionX = centerX + static_cast<int>(static_cast<float>(entity.getWidth()) * std::cos(direction) * 2);
    const auto directionY = centerY + static_cast<int>(static_cast<float>(entity.getHeight()) * std::sin(direction) * 2);
    SDL_SetRenderDrawColor(&renderer, debugColor.r, debugColor.g, debugColor.b, debugColor.a);
    SDL_RenderDrawLine(&renderer, centerX, centerY, directionX, directionY);
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
