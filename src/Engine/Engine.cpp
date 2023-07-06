#include "Engine.h"

#include <SDL2/SDL.h>

#include <iostream>

Engine::Engine(int width, int height)
    : m_width(width)
    , m_height(height) {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Failed to initialize SDL. Aborting." << '\n';
        std::abort();
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
        std::cerr << "Window not established. Aborting program." << '\n';
        std::abort();
    }

    m_surface = SDL_GetWindowSurface(m_window);

    if (!m_surface) {
        std::cerr << "Surface couldn't be created. Aborting program." << '\n';
        std::abort();
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
    SDL_FillRect(m_surface, NULL, SDL_MapRGB(m_surface->format, 0, 0, 0));
    SDL_FillRect(m_surface, &m_testRect, SDL_MapRGB(m_surface->format, 255, 255, 255));
    SDL_BlitSurface(NULL, &m_testRect, m_surface, NULL);
    SDL_UpdateWindowSurface(m_window);
}

void Engine::shutdown() {
    if (m_surface) {
        SDL_FreeSurface(m_surface);
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
