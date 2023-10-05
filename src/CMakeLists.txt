cmake_minimum_required(VERSION 3.25)

project(${PROJECT_NAME})

add_subdirectory(Engine)
set(SOURCE_FILES main.cpp)

add_executable(Breakout ${SOURCE_FILES})

target_link_libraries(
        Breakout
        Engine
        SDL2
        SDL2_ttf
        )
