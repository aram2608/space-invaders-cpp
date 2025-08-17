cmake_minimum_required(VERSION 3.11)
project(space_invaders VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(raylib 3.0 REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(${PROJECT_NAME} 
    space_invaders/src/main.cpp
    space_invaders/src/spaceship.cpp
    space_invaders/src/game.cpp
    space_invaders/src/lasers.cpp
    space_invaders/src/obstacle.cpp
    space_invaders/src/block.cpp
    space_invaders/src/aliens.cpp
    space_invaders/src/mystery_ship.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/space_invaders/include/)

target_link_libraries(${PROJECT_NAME} raylib glfw)

# Checks if OSX and links appropriate frameworks (only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()