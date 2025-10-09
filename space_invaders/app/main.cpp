#include "../si_lib/game/game.hpp"

#include <iostream>
#include <raylib.h>
#include <string>

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

GPU Resources -----
ALWAYS make sure to create the window before loading GPU resources like
- textures etc..

Fonts -----
Fonts are just as easy to load as textures
All you need is a font file and the LoadFontEx

~~~~~~~~~~ General C++ Programming ~~~~~~~~~~

*/

int main() {
    // Hard coded window values w/offest
    int off_set = 50;
    int window_w = 750;
    int window_h = 700;

    // Game window Audio Device //
    // INITIALIZE FIRST BEFORE LOADING GPU RESOURCES //
    InitWindow(window_w + off_set, window_h + (2 * off_set), "C++ - Space Invaders");
    InitAudioDevice();

    // Target FPS of 60
    SetTargetFPS(60);

    // Create our Game object
    Game game;

    // Game loop. Runs will the window is not closed
    while (!WindowShouldClose()) {
        // Tunes
        UpdateMusicStream(game.music);

        // Handles game inputs by state
        game.update_loop();

        // Main logic for drawing to game window
        BeginDrawing();

        game.draw_loop();

        EndDrawing();
    }
    // Close our game window
    CloseWindow();
    CloseAudioDevice();
    return 0;
}