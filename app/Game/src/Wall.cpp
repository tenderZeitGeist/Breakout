//
// Created by zeitgeist on 13.10.23.
//

#include "Game/Wall.h"
#include <Engine/Entity.h>

Wall::Wall(float x, float y)
: Entity(Entity::COLLIDEABLE | Entity::DRAWABLE)
, m_normalX(x)
, m_normalY(y) {
    Entity::getCollideable()->setEnabled(true);
    Entity::getDrawable()->setVisible(false);
}

void Wall::onDebug(bool debug) {
    m_drawable->setVisible(debug);
}

Vector2D Wall::getNormals() const {
    return { m_normalX, m_normalY };
}
