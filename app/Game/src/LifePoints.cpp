#include <Game/LifePoints.h>

LifePoints::LifePoints(int defaultLifePoints)
    : Entity(DRAWABLE)
    , m_defaultLifePoints(defaultLifePoints) {
    setLifePoints(m_defaultLifePoints);
}

void LifePoints::setLifePoints(int lifePoints) {
    m_digit.setValue(lifePoints);
}

int LifePoints::getLifePoints() const {
    return m_digit.getValue();
}

void LifePoints::init(Values v) {
    Entity::init(v);
    m_digit.init(v);
    m_drawable.setVisible(true);
}

void LifePoints::render(SDL_Renderer& renderer) {
    if (!m_drawable.isVisible()) {
        return;
    }

    const auto& color = m_drawable.getColor();
    SDL_SetRenderDrawColor(&renderer, color.r, color.g, color.b, color.a);
    m_digit.render(renderer);
}

void LifePoints::reset() {
    m_digit.setValue(m_defaultLifePoints);
}
