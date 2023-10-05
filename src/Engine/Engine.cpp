#include "Engine.h"
#include "Event.h"
#include "EventManager.h"

#include <chrono>
#include <iostream>

namespace {
    void abortProgram(std::string&& reason) {
        std::cerr << reason + " couldn't be established. Aborting program." << '\n'
                  << "Error reason: " << SDL_GetError() << '\n';
        std::abort();
    }

    using Clock = std::chrono::high_resolution_clock;
    using TimeUnit = std::chrono::milliseconds;

    std::size_t currentTickInMilliseconds() {
        return static_cast<std::size_t>(std::chrono::duration_cast<TimeUnit>(Clock::now().time_since_epoch()).count());
    }
}

Engine::Engine(int width, int height)
    : m_width(width)
    , m_height(height)
    , m_eventManager(std::make_shared<events::EventManager>()){

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        abortProgram("SDL Framework");
    }

    if (TTF_Init() < 0) {
        abortProgram("SDL_ttf");
    }

    m_window = SDL_CreateWindow(
        "Breakout",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        m_width,
        m_height,
        0
    );

    if (!m_window) {
        abortProgram("Window");
    }

    constexpr auto driver = -1;
    constexpr auto renderingFlags = SDL_RENDERER_ACCELERATED;
    m_renderer = SDL_CreateRenderer(m_window, driver, renderingFlags);

    if (!m_renderer) {
        abortProgram("Renderer");
    }

    constexpr auto dimension = 40;
    constexpr auto halfDimension = dimension / 2;
    m_testRect.h = dimension;
    m_testRect.w = dimension;
    m_testRect.x = width / 2 - halfDimension;
    m_testRect.y = height / 2 - halfDimension;

    m_eventManager->subscribe<Engine, events::Shutdown, &Engine::onShutdown>(this);
}

Engine::~Engine() {
    shutdown();
}

int Engine::run() {
    m_previousTick = currentTickInMilliseconds();
    while (m_keepRunning) {
        const auto currentTick = currentTickInMilliseconds();
        auto timeDelta = currentTick - m_previousTick;
        m_previousTick = currentTick;
        pollEvents();

        static constexpr std::size_t kFrameRate = 1000 / 60;
        m_deltaAccumulator += timeDelta;
        if (kFrameRate < m_deltaAccumulator) {
            update();
            draw();
            m_deltaAccumulator -= kFrameRate;
        }
    }
    return 0;
}

void Engine::update() {
    // This should be used to update all the objects of the game.
}

void Engine::draw() {
    // Background color & render.
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);
    // Draw rectangle onto window.
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(m_renderer, &m_testRect);
    SDL_RenderPresent(m_renderer);
}

void Engine::shutdown() {
    m_keepRunning = false;

    if (m_renderer) {
        SDL_DestroyRenderer(m_renderer);
    }

    if (m_window) {
        SDL_DestroyWindow(m_window);
    }

    TTF_Quit();
    SDL_Quit();
}

void Engine::pollEvents() {
    while (SDL_PollEvent(&m_windowEvents)) {
        switch (m_windowEvents.type) {
            case SDL_QUIT:
                m_eventManager->notify(events::Shutdown());
                break;
        }
    }
}

void Engine::onShutdown(events::Shutdown*) {
    shutdown();
}
