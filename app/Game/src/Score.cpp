
#include <Game/Score.h>


namespace {
    constexpr int kMaxDisplayScore{999};
    constexpr std::size_t kBlinkingCount{5};
    constexpr std::size_t kBlinkingInterval{10};

    constexpr std::array<int, Score::kNumOfDigits> kDecimals = {
        1,
        10,
        100,
    };
}


Score::Score()
: Entity(DRAWABLE) {
}

void Score::setScore(int score) {
    m_score = score;
    score = std::min(score, kMaxDisplayScore);

    int j = static_cast<int>(m_digits.size());
    while (j > 0) {
        const std::size_t index = j - 1;
        const auto digit = (score / kDecimals[index]) % 10;
        m_digits[index].setValue(digit);
        --j;
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

    const auto color = m_drawable->getColor();
    SDL_SetRenderDrawColor(&renderer, color.r, color.g, color.b, color.a);
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

void Score::init(Entity::Values v) {
    Entity::init(v);
    const auto size = m_digits.size();
    const auto width = m_rect.w / static_cast<decltype(m_rect.w)>(size);
    m_drawable->setVisible(true);
    for (int i = 0; i < size; ++i) {
        m_digits[i].init({
            .x = m_rect.x + i * width + 10 * i,
            .y = m_rect.y,
            .width = width,
            .height = m_rect.h,
            .color = v.color
        });
    }
}

