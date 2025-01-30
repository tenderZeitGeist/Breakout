//
// Created by zeitgeist on 13.10.23.
//

#pragma once

#include <Engine/Entity.h>

class Wall
    : public Entity {
public:
    explicit Wall(float x, float y);
    void onDebug(bool debug) override;
    [[nodiscard]] Vector2D getNormals() const;
private:
    float m_normalX;
    float m_normalY;
};
