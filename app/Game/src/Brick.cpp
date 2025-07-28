
#include "Game/Brick.h"

Brick::Brick()
    : Entity(COLLIDEABLE | DRAWABLE) {
    m_collideable->setEnabled(true);
}

void Brick::reset() {
    m_collideable->setEnabled(true);
    m_drawable->setVisible(true);
}

int Brick::getValue() const {
    return m_value;
}
