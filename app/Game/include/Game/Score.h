
#pragma once

#include <Engine/Digit.h>

#include <array>

class Score : public Entity {
public:
    static constexpr std::size_t kNumOfDigits{3};

    explicit Score();
    void setScore(int score);
    [[nodiscard]] int getScore() const;

    void setBlinking(bool blinking);

    void init(Values v) override;
    void render(SDL_Renderer& renderer) override;
    void update(float delta) override;

private:
    std::array<Digit, kNumOfDigits> m_digits;
    int m_score{0};
    bool m_blinking{false};
    std::size_t m_blinkCounter{0};
    std::size_t m_blinksLeft{0};
};