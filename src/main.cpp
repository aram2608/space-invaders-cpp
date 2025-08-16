#include <raylib.h>
#include "game.hpp"

/* NOTES
~~~~~~~~~~ raylib ~~~~~~~~~~

Color Schemes ----
Color{red, green, blue, alpha}
Standard RBG with option for opacity with alpha

Draw Methods ----
raylib provides a lot of drawing utlity out of the box
- as opposed to GLEW and glfw3

Look into docs or help for other useful method before creating/rendering
- assets if its something simple like the obstacles in this game

Texture Methods -----
raylib is really easy to use load textures when it is better than
- using the provided draw methods

Just make sure to always unload the texture to not leak memory

~~~~~~~~~~ General C++ Programming ~~~~~~~~~~

*/

int main() {

    // Constants
    Color grey = {29, 29, 27, 255};
    Color yellow = {243, 216, 63, 255};
    int off_set = 50;
    int window_w = 750;
    int window_h = 700;

    // Game window
    InitWindow(window_w + off_set, window_h + (2 * off_set), "C++ - Space Invaders");
    // Game FPS
    SetTargetFPS(60);

    // Create our Game object
    Game game;

    // Game loop. Runs will the window is not closed
    while (!WindowShouldClose()) {

        // Handles game inputs
        game.handle_input();
        game.update();

        // Main logic for drawing to game window
        BeginDrawing();
            // Draw UI
            ClearBackground(grey);
            DrawRectangleRoundedLinesEx({10, 10, 780, 780}, 0.18f, 20, 2, yellow);

            // Draw all defined game assets
            game.draw();
        EndDrawing();
    }

    // Close our game window
    CloseWindow();
    return 0;
}
