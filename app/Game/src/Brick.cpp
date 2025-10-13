#include <Game/Brick.h>

Brick::Brick()
    : Entity(COLLIDABLE | DRAWABLE) {
    m_collidable.setEnabled(true);
}

void Brick::reset() {
    m_collidable.setEnabled(true);
    m_drawable.setVisible(true);
}

int Brick::getValue() const {
    return m_value;
}

void Brick::setValue(int value) {
    m_value = value;
}
