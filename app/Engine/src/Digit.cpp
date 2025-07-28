
#include <Engine/Digit.h>

#include <cassert>

namespace {
    constexpr std::size_t kHLineTop = 0;
    constexpr std::size_t kHLineMiddle = 1;
    constexpr std::size_t kHLineBottom = 2;
    constexpr std::size_t kVLineLeftTop = 3;
    constexpr std::size_t kVLineLeftBottom = 4;
    constexpr std::size_t kVLineRightTop = 5;
    constexpr std::size_t kVLineRightBottom = 6;

    [[nodiscard]] std::vector<std::size_t> valueToLineIndices(int value) {
        switch (value) {
            case 0:
                return {kHLineTop, kHLineBottom, kVLineLeftTop, kVLineLeftBottom, kVLineRightTop, kVLineRightBottom};
            case 1:
                return {kVLineRightTop, kVLineRightBottom};
            case 2:
                return {kHLineTop, kHLineBottom, kHLineMiddle, kVLineRightTop, kVLineLeftBottom};
            case 3:
                return {kHLineTop, kHLineMiddle, kHLineBottom, kVLineRightTop, kVLineRightBottom};
            case 4:
                return {kHLineMiddle, kVLineLeftTop, kVLineRightTop, kVLineRightBottom};
            case 5:
                return {kHLineTop, kHLineMiddle, kHLineBottom, kVLineLeftTop, kVLineRightBottom};
            case 6:
                return {kHLineTop, kHLineMiddle, kHLineBottom, kVLineLeftTop, kVLineLeftBottom, kVLineRightBottom};
            case 7:
                return {kHLineTop, kVLineRightTop, kVLineRightBottom};
            case 8:
                return {kHLineTop, kHLineMiddle, kHLineBottom, kVLineRightTop, kVLineRightBottom, kVLineLeftTop,
                        kVLineLeftBottom};
            case 9:
                return {kHLineTop, kHLineBottom, kHLineMiddle, kVLineRightTop, kVLineLeftTop, kVLineRightBottom};
            default:
                assert(false);
                return {};
        }
    }
}

Digit::Digit()
    : Entity(DRAWABLE)
    , m_lineIndices(valueToLineIndices(m_value)) {}

void Digit::setValue(int value) {
    if (value == m_value) {
        return;
    }
    m_value = value;
    m_lineIndices = valueToLineIndices(m_value);
}

int Digit::getValue() const {
    return m_value;
}

void Digit::render(SDL_Renderer& renderer) {
    if (!m_drawable->isVisible()) {
        return;
    }

    for (auto index: m_lineIndices) {
        SDL_RenderFillRect(&renderer, &m_lines[index]);
    }
}

void Digit::init(Entity::Values v) {
    Entity::init(v);
    resize();
    m_drawable->setVisible(true);
}

void Digit::resize() {
    const auto thickness = m_rect.h / 5;
    const auto halfHeight = m_rect.h / 2;

    const auto x = m_rect.x;
    const auto y = m_rect.y;
    const auto width = m_rect.w;
    const auto height = m_rect.h;

    m_lines[kHLineTop] = {x, y, width, thickness};
    m_lines[kHLineMiddle] = {x, y + halfHeight - thickness / 2, width + 1, thickness};
    m_lines[kHLineBottom] = {x, y + height - thickness, width, thickness};

    m_lines[kVLineLeftTop] = { x , y + 1, thickness, halfHeight + 1};
    m_lines[kVLineLeftBottom] = { x, y + halfHeight, thickness, halfHeight + 1};
    m_lines[kVLineRightTop] = { x + width - thickness, y, thickness + 1, halfHeight + 1};
    m_lines[kVLineRightBottom] = { x + width - thickness, y + halfHeight, thickness + 1, halfHeight + 1};
}
