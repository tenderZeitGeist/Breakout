cmake_minimum_required(VERSION 3.5)
project(Breakout)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG -O0 -Wall -Wextra -Wconversion -Wpedantic")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -flto -fvisibility=hidden")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")

message(STATUS "Debug flags: ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "Release flags: ${CMAKE_CXX_FLAGS_RELEASE}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

find_package(SDL REQUIRED)
find_package(SDL_ttf REQUIRED)
include_directories(${SDL2_LIBRARIES})

set(HEADER_DIR ${PROJECT_SOURCE_DIR}/include)
set(SRC_DIR ${PROJECT_SOURCE_DIR}/app)

add_subdirectory(app)
