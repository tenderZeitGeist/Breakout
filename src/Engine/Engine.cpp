#include "Engine.h"

#include <SDL2/SDL.h>

#include <iostream>

Engine::Engine(std::size_t width, std::size_t height)
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
        static_cast<int>(m_width),
        static_cast<int>(m_height),
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

    update();
    SDL_Delay(10000);
}

Engine::~Engine() {
    if (m_surface) {
        SDL_FreeSurface(m_surface);
    }

    if (m_window) {
        SDL_DestroyWindow(m_window);
    }
}

void Engine::update() {
    SDL_UpdateWindowSurface(m_window);
}