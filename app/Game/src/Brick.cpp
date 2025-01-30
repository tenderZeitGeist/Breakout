
#include "Game/Brick.h"

Brick::Brick()
    : Entity(COLLIDEABLE | DRAWABLE){
    m_collideable->setEnabled(true);
}

std::size_t Brick::getValue() const {
    return m_value;
}
