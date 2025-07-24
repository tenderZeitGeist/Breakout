#pragma once

#include <SDL2/SDL.h>

#include <memory>

struct TextDeleter {
    void operator()(SDL_Texture* texture) const {
        if (!texture) {
            return;
        }
        SDL_DestroyTexture(texture);
    }
};

struct Text {
    std::unique_ptr<SDL_Texture, TextDeleter> texture;
    SDL_Rect position;

    [[nodiscard]] explicit operator bool() const {
        return static_cast<bool>(texture);
    }
};
