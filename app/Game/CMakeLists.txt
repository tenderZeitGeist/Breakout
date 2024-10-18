cmake_minimum_required(VERSION 3.5)

project(Game C CXX)

set(DIR_INCLUDE ${CMAKE_CURRENT_LIST_DIR}/include)
set(DIR_SOURCE ${CMAKE_CURRENT_LIST_DIR}/src)

set(GAME_HEADER_FILES
        "${DIR_INCLUDE}/Game/Ball.h"
        "${DIR_INCLUDE}/Game/Brick.h"
        "${DIR_INCLUDE}/Game/Game.h"
        "${DIR_INCLUDE}/Game/GameScene.h"
        "${DIR_INCLUDE}/Game/GameEvent.h"
        "${DIR_INCLUDE}/Game/Paddle.h"
        "${DIR_INCLUDE}/Game/Scene.h"
        "${DIR_INCLUDE}/Game/Wall.h"
)

set(GAME_SOURCE_FILES
        "${DIR_SOURCE}/Ball.cpp"
        "${DIR_SOURCE}/Brick.cpp"
        "${DIR_SOURCE}/Game.cpp"
        "${DIR_SOURCE}/GameScene.cpp"
        "${DIR_SOURCE}/Paddle.cpp"
        "${DIR_SOURCE}/Wall.cpp"
)

add_library(${PROJECT_NAME} STATIC ${GAME_SOURCE_FILES} ${GAME_HEADER_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE Engine)

target_include_directories(
        ${PROJECT_NAME}
        PUBLIC
            ${DIR_INCLUDE}
        PRIVATE
            ${DIR_SOURCE}
)
