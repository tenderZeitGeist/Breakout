
#include <SDL2/SDL_ttf.h>

#include <Engine/Configuration.h>
#include <Engine/Text.h>
#include <Engine/TextureRenderer.h>

TextureRenderer::TextureRenderer(std::reference_wrapper<SDL_Renderer> renderer, std::reference_wrapper<TTF_Font> normalFont, std::reference_wrapper<TTF_Font> headlineFont)
    : m_renderer(renderer)
    , m_mediumFont(normalFont)
    , m_largeFont(headlineFont){
}

Text TextureRenderer::createText(std::string_view text, bool large) const {
    auto& selectedFont = large ? m_largeFont.get() : m_mediumFont.get();
    const auto surface = [font = &selectedFont, text = text.data()]() -> SDL_Surface* {
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
