
#pragma once

#include <SDL2/SDL.h>

#include <memory>
#include <string_view>


struct SDL_Renderer;
struct TTF_Font;
struct Text;

class TextureRenderer {
public:
    explicit TextureRenderer(std::reference_wrapper<SDL_Renderer> renderer, std::reference_wrapper<TTF_Font> font);
    [[nodiscard]] Text createText(std::string_view text) const;

private:
    std::reference_wrapper<SDL_Renderer> m_renderer;
    std::reference_wrapper<TTF_Font> m_font;
};