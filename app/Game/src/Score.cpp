
#include <Game/Score.h>

namespace {
    constexpr int kMaxDisplayScore{999};
    constexpr std::size_t kBlinkingCount{5};
    constexpr std::size_t kBlinkingInterval{10};
}

void Score::setScore(int score) {
    m_score = score;
    score = std::min(score, kMaxDisplayScore);

    std::size_t i{0};
    while (score > 0) {
        const auto digit = score % 10;
        m_digits[i].setValue(digit);
        score /= 10;
        ++i;
    }

    if (i == 2) {
        return;
    }

    while (i < 2) {
        m_digits[i].setValue(0);
        ++i;
    }
}

int Score::getScore() const {
    return m_score;
}

void Score::setBlinking(bool blinking) {
    if (blinking) {
        m_blinksLeft = kBlinkingCount;
        m_blinkCounter = 0;
    } else {
        m_drawable->setVisible(true);
        m_blinksLeft = 0;
        m_blinkCounter = 0;
    }
}

void Score::render(SDL_Renderer& renderer) {
    if (!m_drawable->isVisible()) {
        return;
    }

    for (auto& digit: m_digits) {
        digit.render(renderer);
    }
}

void Score::update(float delta) {
    if (m_blinksLeft == 0) {
        return;
    }

    --m_blinkCounter;
    const auto expired = m_blinkCounter < 0;
    if (expired) {
        m_blinkCounter = kBlinkingCount;
        const auto isVisible = m_drawable->isVisible();
        m_drawable->setVisible(!isVisible);
        if (isVisible) {
            --m_blinksLeft;
        }
    }
}

