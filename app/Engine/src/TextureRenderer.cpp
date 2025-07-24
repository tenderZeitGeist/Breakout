
#include <SDL2/SDL_ttf.h>

#include <Engine/Configuration.h>
#include <Engine/Text.h>
#include <Engine/TextureRenderer.h>

TextureRenderer::TextureRenderer(std::reference_wrapper<SDL_Renderer> renderer, std::reference_wrapper<TTF_Font> font)
    : m_renderer(renderer)
    , m_font(font) {
}

Text TextureRenderer::createText(std::string_view text) const {
    const auto surface = [font = &m_font.get(), text = text.data()]() -> SDL_Surface* {
        try {
            return TTF_RenderText_Blended(font, text, config::kWhiteColor);
        } catch (...) {
            return nullptr;
        }
    }();

    if (!surface) {
        return {};
    }
    const auto texture = [&surface, renderer = &m_renderer.get()]() -> SDL_Texture* {
        try {
            return SDL_CreateTextureFromSurface(renderer, surface);
        } catch (...) {
            SDL_FreeSurface(surface);
            return nullptr;
        }
    }();

    if (!texture) {
        return {};
    }

    return {.texture = std::unique_ptr<SDL_Texture, TextDeleter>(texture), .position = {}};
}
