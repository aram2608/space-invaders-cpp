#include <raylib.h>
#include "game.hpp"

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

    // Create our Game object
    Game game;

    // Game loop. Runs will the window is not closed
    while (!WindowShouldClose()) {

        // Handles game inputs
        game.handle_input();
        game.update();

        BeginDrawing();
            // Draw a clear grey background
            ClearBackground(GREY);
            // Game logic
            game.draw();
        EndDrawing();
    }

    // Close our game window
    CloseWindow();
    return 0;
}
