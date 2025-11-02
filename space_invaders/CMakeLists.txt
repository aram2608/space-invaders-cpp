add_library(si_lib
    si_lib/aliens/aliens.cpp
    si_lib/aliens/mystery_ship.cpp
    si_lib/game/game.cpp
    si_lib/obstacles/block.cpp
    si_lib/obstacles/obstacle.cpp
    si_lib/ship/lasers.cpp
    si_lib/ship/spaceship.cpp
    si_lib/ui/ui.cpp
)

find_package(raylib 3.0 REQUIRED)
find_package(glfw3 REQUIRED)

target_link_libraries(si_lib 
    PUBLIC 
    raylib 
    glfw
)

target_include_directories(si_lib
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/si_lib/
)

target_compile_options(si_lib
    PRIVATE
    -Wall 
    -Wextra 
    -Wpedantic 
    -Wconversion
    -Wpessimizing-move
    -Wredundant-move
    -Wmove
    -Wrange-loop-construct
)

add_executable(space_invaders
    app/main.cpp
)

# raylib and gflw are propogated from the library
target_link_libraries(space_invaders
    PRIVATE
    si_lib
)

# Checks if OSX and links appropriate frameworks (only required on MacOS)
if(APPLE)
    target_link_libraries(space_invaders
        PRIVATE
            "-framework Cocoa"
            "-framework IOKit"
            "-framework OpenGL"
    )
endif()