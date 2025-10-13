#pragma once

#include <Engine/Shape.h>
#include <SDL2/SDL_render.h>

struct RenderVisitor {
    explicit RenderVisitor(SDL_Renderer& renderer);
    void operator()(const RectShape& shape) const;
    void operator()(const CircleShape& shape) const;
    SDL_Renderer& m_renderer;
};
