//
// Created by zeitgeist on 06.10.23.
//

#pragma once

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_keycode.h>

class Scene {
public:
    virtual ~Scene() = default;
    virtual void update(float delta) = 0;
    virtual void render(SDL_Renderer& renderer) = 0;
    virtual void enter() = 0;
    virtual void exit() = 0;
};
