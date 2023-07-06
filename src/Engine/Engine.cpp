#include "Engine.h"

#include <SDL2/SDL.h>

#include <iostream>

namespace {
    void abortProgram(std::string&& reason) {
        std::cerr << reason + " couldn't be established. Aborting program." << '\n'
                  << "Error reason: " << SDL_GetError() << '\n';
        std::abort();
    }
}

Engine::Engine(int width, int height)
    : m_width(width)
    , m_height(height) {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        abortProgram("SDL Framework");
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
}

Engine::~Engine() {
    shutdown();
}

void Engine::run() {
    while(m_keepRunning) {
        pollEvents();
        update();
        draw();
    }
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
   if (m_renderer) {
       SDL_DestroyRenderer(m_renderer);
   }

    if (m_window) {
        SDL_DestroyWindow(m_window);
    }
}

void Engine::pollEvents() {
    while (SDL_PollEvent(&m_windowEvents)) {
        switch(m_windowEvents.type) {
            case SDL_QUIT:
                m_keepRunning = false;
                break;
        }
    }
}
