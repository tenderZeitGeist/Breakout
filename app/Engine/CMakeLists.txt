cmake_minimum_required(VERSION 3.2)

project(Engine C CXX)

set(ENGINE_HEADER_FILES
        "Configuration.h"
        "Collideable.h"
        "Drawable.h"
        "Engine.h"
        "Entity.h"
        "Event.h"
        "EventManager.h"
        "Moveable.h"
)

set(ENGINE_SOURCE_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/src/Collideable.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/Drawable.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/Engine.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/Entity.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/Moveable.cpp"
)

add_library(${PROJECT_NAME} STATIC ${ENGINE_SOURCE_FILES} ${ENGINE_HEADER_FILES})

target_include_directories(
        ${PROJECT_NAME}
        PRIVATE
        "${CMAKE_SOURCE_DIR}/app"
)
