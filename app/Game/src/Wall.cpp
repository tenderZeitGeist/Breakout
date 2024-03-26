//
// Created by zeitgeist on 13.10.23.
//

#include "Game/Wall.h"
#include <Engine/Entity.h>

#include "Engine/Configuration.h"

Wall::Wall()
: Entity(Entity::COLLIDEABLE) {
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
