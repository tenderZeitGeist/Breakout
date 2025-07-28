
#pragma once

#include <Engine/Digit.h>

class LifePoints : public Entity {
public:
    explicit LifePoints(int defaultLifePoints);

    void setLifePoints(int lifePoints);
    [[nodiscard]] int getLifePoints() const;

    void init(Values v) override;
    void render(SDL_Renderer& renderer) override;
    void reset() override;

private:
    Digit m_digit;
    int m_defaultLifePoints;
};