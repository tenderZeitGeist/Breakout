
#pragma once

#include <Engine/Digit.h>

class LifePoints : public Entity {
public:
    explicit LifePoints();

    void setLifePoints(int lifePoints);
    int getLifePoints() const;

    void init(Values v) override;
    void render(SDL_Renderer& renderer) override;

private:
    Digit m_digit;
};