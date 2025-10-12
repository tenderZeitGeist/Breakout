#include <Engine/Engine.h>
#include <Engine/Configuration.h>
#include <Engine/Event.h>
#include <Engine/EventManager.h>
#include <Engine/TextureRenderer.h>

#include <chrono>
#include <iostream>

#include <Game/Game.h>
#include <Game/GameScene.h>

namespace {
void abortProgram(std::string_view reason) {
    std::cerr << reason << " couldn't be established. Aborting program." << '\n'
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
    : m_eventManager(std::make_shared<events::EventManager>())
    , m_keyHandler(m_eventManager)
    , m_game(m_eventManager, m_keyHandler)
    , m_width(width)
    , m_height(height) {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        abortProgram("SDL Framework");
    }

    if (TTF_Init() < 0) {
        abortProgram("SDL_ttf");
    }

    m_window = SDL_CreateWindow("Breakout", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, 0);

    if (!m_window) {
        abortProgram("Window");
    }

    constexpr auto driver = -1;
    constexpr auto renderingFlags = SDL_RENDERER_ACCELERATED;
    m_renderer = SDL_CreateRenderer(m_window, driver, renderingFlags);

    if (!m_renderer) {
        abortProgram("Renderer");
    }

    m_eventManager->subscribe<Engine, events::Shutdown, &Engine::onShutdown>(this);

    m_mediumFont = TTF_OpenFont(FONT_PATH, 28);
    m_largeFont = TTF_OpenFont(FONT_PATH, 56);
    const auto textureRenderer = TextureRenderer(std::ref(*m_renderer), std::ref(*m_mediumFont), std::ref
                                                 (*m_largeFont));
    m_game.initializeGame(textureRenderer);
}

Engine::~Engine() {
    shutdown();
}

int Engine::run() {
    m_previousTick = currentTickInMilliseconds();

    while (m_keepRunning) {
        pollEvents();
        const auto currentTick = currentTickInMilliseconds();
        const auto timeDelta = currentTick - m_previousTick;
        m_previousTick = currentTick;

        m_deltaAccumulator += timeDelta;
        if (config::frameTimes > m_deltaAccumulator) {
            continue;
        }
        update();
        draw();
        m_deltaAccumulator -= config::frameTimes;
    }

    return 0;
}

void Engine::update() {
    m_game.update(config::frameTimesInFloat);
}

void Engine::draw() {
    SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 0xff);
    SDL_RenderClear(m_renderer);

    m_game.render(*m_renderer);

    SDL_RenderPresent(m_renderer);
}

void Engine::shutdown() {
    if (m_renderer) {
        SDL_DestroyRenderer(m_renderer);
    }

    if (m_window) {
        SDL_DestroyWindow(m_window);
    }

    if (m_mediumFont) {
        TTF_CloseFont(m_mediumFont);
    }

    if (m_largeFont) {
        TTF_CloseFont(m_largeFont);
    }

    TTF_Quit();
    SDL_Quit();
}

void Engine::pollEvents() {
    static SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                m_eventManager->notify(events::Shutdown());
                break;
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                m_eventManager->notify(events::KeyPress(event.type, event.key.keysym.sym));
                break;
        }
    }
}

void Engine::onShutdown(events::Shutdown&) {
    m_keepRunning = false;
}
