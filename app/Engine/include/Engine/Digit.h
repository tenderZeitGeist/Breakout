
#pragma once

#include <Engine/Entity.h>

#include <array>
#include <vector>

class Digit : public Entity {
    static constexpr std::size_t kNumOfLines = 8;

public:
    void setValue(int value);
    [[nodiscard]] int getValue() const;

    void init(Values v) override;
    void render(SDL_Renderer& renderer) override;

private:
    void resize();

    int m_value{0};
    std::array<SDL_Rect, kNumOfLines> m_lines{};
    std::vector<std::size_t> m_lineIndices;
};