#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class SDL_Window;
class SDL_Surface;

class Engine {
public:
    explicit Engine(int width, int height);
    ~Engine();

    void run();

private:
    void update();
    void draw();
    void shutdown();
    void pollEvents();

private:
    SDL_Window* m_window{nullptr};
    SDL_Renderer* m_renderer{nullptr};
    SDL_Event m_windowEvents{};

    SDL_Rect m_testRect{};

    int m_width;
    int m_height;

    bool m_keepRunning{true};
};
