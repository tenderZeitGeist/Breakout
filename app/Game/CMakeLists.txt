cmake_minimum_required(VERSION 3.2)

project(Game C CXX)

set(GAME_HEADER_FILES
        "Game.h"
        "GameScene.h"
        "Paddle.h"
        "Scene.h"
)

set(GAME_SOURCE_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/src/Game.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/GameScene.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/Paddle.cpp"
)

add_library(${PROJECT_NAME} STATIC ${GAME_SOURCE_FILES} ${GAME_HEADER_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE Engine)

target_include_directories(
        ${PROJECT_NAME}
        PRIVATE
        "${CMAKE_SOURCE_DIR}/app"
        "${CMAKE_CURRENT_SOURCE_DIR}"
)
