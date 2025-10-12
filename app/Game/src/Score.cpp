#include <Game/Score.h>

namespace {
    constexpr int kMaxDisplayScore{999};
    constexpr int kBlinkingCount{5};
    constexpr int kBlinkingInterval{12}; // 16ms * 12 ticks = 192 ms per blink

    constexpr std::array<int, Score::kNumOfDigits> kDecimals = {
        1,
        10,
        100,
    };
}


Score::Score()
    : Entity(DRAWABLE) {
}

void Score::increaseScore(int points) {
    setScore(getScore() + points);
}

void Score::setBlinking(bool blinking) {
    if (blinking) {
        m_blinksLeft = kBlinkingCount;
    } else {
        m_drawable.setVisible(true);
        m_blinksLeft = 0;
    }
    m_blinkTicksCounter = 0;
}

void Score::render(SDL_Renderer& renderer) {
    if (!m_drawable.isVisible()) {
        return;
    }

    const auto color = m_drawable.getColor();
    SDL_SetRenderDrawColor(&renderer, color.r, color.g, color.b, color.a);
    for (auto& digit: m_digits) {
        digit.render(renderer);
    }
}

void Score::update(float) {
    if (m_blinksLeft <= 0) {
        return;
    }

    m_blinkTicksCounter = (m_blinkTicksCounter + 1) % kBlinkingInterval;
    if (m_blinkTicksCounter != 0) { // not expired
        return;
    }

    const auto isVisible = m_drawable.isVisible();
    m_drawable.setVisible(!isVisible);
    if (isVisible) {
        --m_blinksLeft;
    }

    if (m_blinksLeft <= 0) {
        setBlinking(false);
    }
}

void Score::init(Entity::Values v) {
    Entity::init(v);
    const auto size = static_cast<int>(m_digits.size());
    const auto width = m_rect.w / static_cast<decltype(m_rect.w)>(size);
    const auto height = m_rect.h;
    m_drawable.setVisible(true);

    for (int i = 0; i < size; ++i) {
        const auto offset = size - i - 1;
        constexpr int spacing = 10;
        m_digits[i].init({
            .x = m_rect.x + offset * width + spacing * offset,
            .y = m_rect.y,
            .width = width,
            .height = height,
            .color = v.color
        });
    }
}

void Score::reset() {
    setBlinking(false);
    setScore(0);
}

void Score::setScore(int score) {
    m_score = score;
    score = std::min(score, kMaxDisplayScore);

    for (auto& m_digit: m_digits) {
        const auto digit = score % 10;
        m_digit.setValue(digit);
        score /= 10;
    }
}

int Score::getScore() const {
    return m_score;
}
