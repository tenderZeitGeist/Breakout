#pragma once

#include <SDL2/SDL.h>

class SDL_Window;
class SDL_Surface;

class Engine {
public:
    explicit Engine(int width, int height);
    ~Engine();

    void update();

private:
    int m_width;
    int m_height;
    SDL_Window* m_window{nullptr};
    SDL_Surface* m_surface{nullptr};
};
