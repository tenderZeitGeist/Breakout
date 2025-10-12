#pragma once

#include <SDL2/SDL.h>

#include <memory>
#include <string_view>


struct TTF_Font;
struct Text;

class TextureRenderer {
public:
    explicit TextureRenderer(std::reference_wrapper<SDL_Renderer> renderer, std::reference_wrapper<TTF_Font>
            normalFont, std::reference_wrapper<TTF_Font> headlineFont);
    [[nodiscard]] Text createText(std::string_view text, bool large = false) const;

private:
    std::reference_wrapper<SDL_Renderer> m_renderer;
    std::reference_wrapper<TTF_Font> m_mediumFont;
    std::reference_wrapper<TTF_Font> m_largeFont;
};