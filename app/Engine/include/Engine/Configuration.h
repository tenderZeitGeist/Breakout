//
// Created by zeitgeist on 12.10.23.
//

#pragma once

#include <SDL2/SDL.h>

#include <array>

namespace config {
    static constexpr int windowWidth = 800;
    static constexpr int windowHeight = 950;
    static constexpr int windowHalfWidth = windowWidth / 2;
    static constexpr int windowHalfHeight = windowHeight / 2;

    static constexpr int slotWidthDivisor = 16;
    static constexpr int slotHeightDivisor = 45;
    static constexpr int slotWidth = windowWidth / slotWidthDivisor;
    static constexpr int slotHeight = windowHeight / slotHeightDivisor;
    static constexpr int slotHalfWidth = slotWidth / 2;
    static constexpr int slotHalfHeight = slotHeight / 2;
    static constexpr int slotSpacing = (windowWidth - 2 * slotHeight - 14 * slotWidth) / 13;

    static constexpr int frameRate = 60;
    static constexpr int frameTimes = 1000 / frameRate;
    static constexpr float frameTimesInFloat = static_cast<float>(frameTimes);

    static constexpr SDL_Color kBricksFillStyle1 = {0xff, 0xf0, 0x00, 0xff };
    static constexpr SDL_Color kBricksFillStyle2 = {0x00, 0x80, 0x00, 0xff };
    static constexpr SDL_Color kBricksFillStyle3 = {0xff, 0xa5, 0x00, 0xff };
    static constexpr SDL_Color kBricksFillStyle4 = {0xff, 0x00, 0x00, 0xff };
    static constexpr SDL_Color kDebugColor = {0xff, 0x00, 0x00, 0xff };
    static constexpr std::array kBricksFillStyles{
        kBricksFillStyle1,
        kBricksFillStyle2,
        kBricksFillStyle3,
        kBricksFillStyle4,
    };
}
