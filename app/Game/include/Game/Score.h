
#pragma once

#include <Engine/Digit.h>

#include <array>

class Score : public Entity {
public:
    static constexpr std::size_t kNumOfDigits{3};

    explicit Score();
    void increaseScore(int points);
    void setBlinking(bool blinking);

    void init(Values v) override;
    void render(SDL_Renderer& renderer) override;
    void update(float) override;
    void reset() override;

private:
    void setScore(int score);
    [[nodiscard]] int getScore() const;

    std::array<Digit, kNumOfDigits> m_digits;
    int m_score{0};
    bool m_blinking{false};
    int m_blinkTicksCounter{0};
    int m_blinksLeft{0};
};