cmake_minimum_required(VERSION 3.25)
project(Breakout)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")

find_package(SDL REQUIRED)
find_package(SDL_ttf REQUIRED)
include_directories(${SDL2_LIBRARIES})

set(HEADER_DIR ${PROJECT_SOURCE_DIR}/include)
set(SRC_DIR ${PROJECT_SOURCE_DIR}/app)

add_subdirectory(app)
