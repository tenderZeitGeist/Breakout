#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <memory>

namespace events{
    class EventManager;
    struct Shutdown;
}

class Engine {
public:
    explicit Engine(int width, int height);
    ~Engine();

    int run();

private:
    void update();
    void draw();
    void shutdown();
    void pollEvents();

    void onShutdown(events::Shutdown*);

private:
    SDL_Window* m_window{nullptr};
    SDL_Renderer* m_renderer{nullptr};
    SDL_Event m_windowEvents{};

    SDL_Rect m_testRect{};

    std::shared_ptr<events::EventManager> m_eventManager;

    std::size_t m_deltaAccumulator{0};
    std::size_t m_previousTick{0};

    int m_width;
    int m_height;

    bool m_keepRunning{true};
};
