#include <raylib.h>
#include <string>
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

GPU Resources -----
ALWAYS make sure to create the window before loading GPU resources like
- textures etc..

Fonts -----
Fonts are just as easy to load as textures
All you need is a font file and the LoadFontEx

~~~~~~~~~~ General C++ Programming ~~~~~~~~~~

*/

// Function to reformat a string with leading zeros
std::string format_trail_zeros(int number, int width) {
    std::string num_text = std::to_string(number);
    int trailing_zeros = width - num_text.length();
    return num_text = std::string(trailing_zeros, '0') + num_text;
}

// Function to reformat level displayed on UI
std::string format_level(int number) {
    if(number < 10) {
        std::string num_text = std::to_string(number);
        return num_text = '0' + num_text;
    } else {
        std::string num_text = std::to_string(number);
        return num_text;
    }
}

int main() {

    // Constants //
    Color grey = {29, 29, 27, 255};
    Color yellow = {243, 216, 63, 255};
    int off_set = 50;
    int window_w = 750;
    int window_h = 700;
    std::string level_display = "LEVEL";

    // Game window Audio Device //
    // INITIALIZE FIRST BEFORE LOADING GPU RESOURCES //
    InitWindow(window_w + off_set, window_h + (2 * off_set), "C++ - Space Invaders");
    InitAudioDevice();

    // Font - 64 pixels in size
    Font font = LoadFontEx("font/monogram.ttf", 64, 0, 0);
    // UI component to display number of lives remaining
    Texture2D ship_image = LoadTexture("assets/spaceship.png");

    // Target FPS of 60
    SetTargetFPS(60);

    // Create our Game object
    Game game;

    // Game loop. Runs will the window is not closed
    while (!WindowShouldClose()) {
        // Tunes
        UpdateMusicStream(game.music);

        // Handles game inputs by state
        switch (game.state) {
            case GameState::Title: game.update_title(); break;
            case GameState::Playing: game.update_playing(); break;
            case GameState::Paused: game.update_paused(); break;
            case GameState::GameOver: game.update_gameover(); break;
        }

        // Main logic for drawing to game window
        BeginDrawing();

            // Draw UI Components
            ClearBackground(grey);
            DrawRectangleRoundedLinesEx({10, 10, 780, 780}, 0.18f, 20, 2, yellow);
            DrawLineEx({25, 730}, {775, 730}, 3, yellow);

            // Level of game
            std::string level_num = format_level(game.level);
            std::string level = level_display + " " + level_num;
            DrawTextEx(font, level.c_str(), {565, 740}, 34, 2, yellow);

            // Lives remaining
            float x = 50.0;
            for(int i = 0; i < game.lives; i++) {
                DrawTextureV(ship_image, {x, 745}, WHITE);
                x += 50;
            }

            // Scoreboard
            DrawTextEx(font, "SCORE", {50, 15}, 34, 2, yellow);
            std::string score_txt = format_trail_zeros(game.score, 5);
            DrawTextEx(font, score_txt.c_str(), {50, 40}, 34, 2, yellow);

            DrawTextEx(font, "HIGH SCORE", {570, 15}, 34, 2, yellow);
            std::string high_scr_txt = format_trail_zeros(game.high_score, 5);
            DrawTextEx(font, high_scr_txt.c_str(), {655, 40}, 34, 2, yellow);

            // Draw all defined game assets
            game.draw();
        EndDrawing();
    }
    // Close our game window
    CloseWindow();
    CloseAudioDevice();
    return 0;
}