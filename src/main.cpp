#include <raylib.h>
#include "include/spaceship.hpp"

// In raylib, Color{red, green, blue, alpha}

// Constants
Color GREY = {29, 29, 27, 255};

int main() {

    int windowWidth = 750;
    int windowHeight = 700;

    // Game window
    InitWindow(windowWidth, windowHeight, "C++ - Space Invaders");
    // Game FPS
    SetTargetFPS(60);

    // Create our SpaceShip Object
    SpaceShip ship;

    // Game loop. Runs will the window is not closed
    while (!WindowShouldClose()) {
        BeginDrawing();
            // Draw a clear grey background
            ClearBackground(GREY);
            ship.draw();

        EndDrawing();
    }

    // Close our game window
    CloseWindow();
    return 0;
}
