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
    [[nodiscard]] std::pair<float, float> getNormals() const;
private:
    float m_normalX;
    float m_normalY;
};