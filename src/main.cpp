#include "raylib.h"

int main() {

    int windowWidth = 750;
    int windowHeight = 700;

    // Game window
    InitWindow(windowWidth, windowHeight, "C++ - Space Invaders");
    // Game FPS
    SetTargetFPS(60);

    // Game loop. Runs will the window is not closed
    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(Color{255, 255, 255, 255});
        EndDrawing();
    }

    // Close our game window
    CloseWindow();
    return 0;
}
