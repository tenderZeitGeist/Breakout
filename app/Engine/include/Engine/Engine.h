#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <Game/Game.h>

#include <atomic>
#include <thread>
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

    void onShutdown(events::Shutdown&);

private:
    SDL_Window* m_window{nullptr};
    SDL_Renderer* m_renderer{nullptr};

    std::thread m_pollThread;
    std::shared_ptr<events::EventManager> m_eventManager;
    Game m_game;

    std::size_t m_deltaAccumulator{0};
    std::size_t m_previousTick{0};

    int m_width;
    int m_height;

    std::atomic<bool> m_keepRunning{true};
};
