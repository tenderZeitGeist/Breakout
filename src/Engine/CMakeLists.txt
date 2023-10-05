cmake_minimum_required(VERSION 3.2)

project(Engine C CXX)

set(SOURCE_FILES
        Engine.h
        Engine.cpp
        EventManager.h
        EventManager.cpp
        Game.h
        Game.cpp
        )

add_library(${PROJECT_NAME} STATIC SHARED ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
