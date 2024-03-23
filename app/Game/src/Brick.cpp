
#include "Game/Brick.h"

Brick::Brick()
    : Entity(COLLIDEABLE | DRAWABLE){
    m_collideable->setEnabled(true);
}
