//
// Created by zeitgeist on 13.10.23.
//

#include "Game/Wall.h"
#include <Engine/Entity.h>

#include "Engine/Configuration.h"

namespace {
    bool almostEqual(float a, float b) {
        static constexpr auto epsilon = 0.00001f;
        return std::abs(a - b) < epsilon;
    }
}

Wall::Wall(float x, float y)
: Entity(Entity::COLLIDEABLE)
, m_normalX(x)
, m_normalY(y) {
    Entity::getCollideable()->setEnabled(true);
}

void Wall::onDebug(bool debug) {
    if (debug) {
        m_drawable = std::make_unique<Drawable>(*this);
        m_drawable->setColor(config::kDebugColor);
    } else {
        m_drawable.reset();
    }
}

std::pair<float, float> Wall::getNormals() const {
    return std::make_pair(m_normalX, m_normalY);
}
