
#include <Game/MenuScene.h>

#include <Engine/Configuration.h>

#include <SDL2/SDL_ttf.h>

#include <string_view>


namespace {
SDL_Texture* createText(std::string_view text) {
    auto surface = TTF_RenderText_Blended();
}
}