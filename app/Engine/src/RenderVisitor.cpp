#include <Engine/Entity.h>
#include <Engine/RenderVisitor.h>

RenderVisitor::RenderVisitor(SDL_Renderer& renderer)
    : m_renderer(renderer) {
}


void RenderVisitor::operator()(const RectShape& shape) const {
    SDL_RenderFillRect(&m_renderer, &shape.getBoundingBox());
}

void RenderVisitor::operator()(const CircleShape& shape) const {
    const auto radius = shape.getRadius();
    const auto diameter = radius * 2;
    const auto centerX = shape.getEntity().get().getCenterX();
    const auto centerY = shape.getEntity().get().getCenterY();

    int x = radius - 1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int error = dx - diameter;

    std::array<SDL_Point, 8> points{};
    while (x >= y) {
        points = {{{centerX + x, centerY - y},
                   {centerX + x, centerY + y},
                   {centerX - x, centerY - y},
                   {centerX - x, centerY + y},
                   {centerX + y, centerY - x},
                   {centerX + y, centerY + x},
                   {centerX - y, centerY - x},
                   {centerX - y, centerY + x}}};
        SDL_RenderDrawLines(&m_renderer, points.data(), points.size());

        if (error <= 0) {
            ++y;
            error += dy;
            dy += 2;
        }
        if (error > 0) {
            --x;
            dx += 2;
            error += dx - diameter;
        }
    }
}
