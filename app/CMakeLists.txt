cmake_minimum_required(VERSION 3.25)

project(${PROJECT_NAME})

add_subdirectory(Engine)
add_subdirectory(Game)

set(SOURCE_FILES ${ENGINE_SOURCE_FILES} ${GAME_SOURCE_FILES} main.cpp)

add_executable(Breakout ${SOURCE_FILES})

set(CMAKE_INCLUDE_CURRENT_DIR ON)

target_link_libraries(
        ${PROJECT_NAME}
        PUBLIC
        Engine
        Game
        SDL2
        SDL2_ttf
)
