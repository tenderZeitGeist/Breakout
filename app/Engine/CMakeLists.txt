cmake_minimum_required(VERSION 3.25)

project(Engine C CXX)

set(DIR_SOURCE  ${CMAKE_CURRENT_LIST_DIR}/src)
set(DIR_INCLUDE ${CMAKE_CURRENT_LIST_DIR}/include)

set(ENGINE_HEADER_FILES
        "${DIR_INCLUDE}/Engine/Configuration.h"
        "${DIR_INCLUDE}/Engine/Collidable.h"
        "${DIR_INCLUDE}/Engine/CollisionVisitor.h"
        "${DIR_INCLUDE}/Engine/Component.h"
        "${DIR_INCLUDE}/Engine/Digit.h"
        "${DIR_INCLUDE}/Engine/Drawable.h"
        "${DIR_INCLUDE}/Engine/Engine.h"
        "${DIR_INCLUDE}/Engine/Entity.h"
        "${DIR_INCLUDE}/Engine/Event.h"
        "${DIR_INCLUDE}/Engine/EventManager.h"
        "${DIR_INCLUDE}/Engine/KeyHandler.h"
        "${DIR_INCLUDE}/Engine/Moveable.h"
        "${DIR_INCLUDE}/Engine/PerformanceMetrics.h"
        "${DIR_INCLUDE}/Engine/RenderVisitor.h"
        "${DIR_INCLUDE}/Engine/Shape.h"
        "${DIR_INCLUDE}/Engine/TextureRenderer.h"
        "${DIR_INCLUDE}/Engine/Text.h"
)

set(ENGINE_SOURCE_FILES
        "${DIR_SOURCE}/Collidable.cpp"
        "${DIR_SOURCE}/CollisionVisitor.cpp"
        "${DIR_SOURCE}/Component.cpp"
        "${DIR_SOURCE}/Digit.cpp"
        "${DIR_SOURCE}/Drawable.cpp"
        "${DIR_SOURCE}/Engine.cpp"
        "${DIR_SOURCE}/Entity.cpp"
        "${DIR_SOURCE}/KeyHandler.cpp"
        "${DIR_SOURCE}/Moveable.cpp"
        "${DIR_SOURCE}/TextureRenderer.cpp"
        "${DIR_SOURCE}/PerformanceMetrics.cpp"
        "${DIR_SOURCE}/RenderVisitor.cpp"
        "${DIR_SOURCE}/Shape.cpp"
)

add_library(${PROJECT_NAME} STATIC ${ENGINE_SOURCE_FILES} ${ENGINE_HEADER_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE Game)

target_include_directories(
        ${PROJECT_NAME}
        PUBLIC
            ${DIR_INCLUDE}
        PRIVATE
            ${DIR_SOURCE}
)
