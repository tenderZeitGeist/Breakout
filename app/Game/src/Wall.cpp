#include <Engine/Entity.h>
#include <Game/Wall.h>

Wall::Wall(float x, float y)
: Entity(Entity::COLLIDABLE | Entity::DRAWABLE)
, m_normalX(x)
, m_normalY(y) {
    Entity::getCollidable().get().setEnabled(true);
    Entity::getDrawable().get().setVisible(false);
}

void Wall::onDebug(bool debug) {
    m_drawable.setVisible(debug);
}

Vector2D Wall::getNormals() const {
    return { m_normalX, m_normalY };
}
