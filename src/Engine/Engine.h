#pragma once

#include <SDL2/SDL.h>

class SDL_Window;
class SDL_Surface;

class Engine {
public:
    explicit Engine(std::size_t width, std::size_t height);
    ~Engine();

    void update();

private:
    std::size_t m_width;
    std::size_t m_height;
    SDL_Window* m_window{nullptr};
    SDL_Surface* m_surface{nullptr};
};
