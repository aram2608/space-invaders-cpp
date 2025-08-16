enum class GameState { Title, Playing, Paused, GameOver };

struct Game {
    GameState state = GameState::Title;
    int lives = 3;
    int score = 0;
    int high_score = 0;
    int level = 1;
    Music music;
    // assets...
    // methods: reset(), drawPlaying(), drawTitle(), drawGameOver(), etc.
};

void updateTitle(Game& g) {
    if (IsKeyPressed(KEY_ENTER)) {
        // (Re)start the game
        g.reset();
        PlayMusicStream(g.music);
        g.state = GameState::Playing;
    }
}

void updatePlaying(Game& g, float dt) {
    UpdateMusicStream(g.music);
    // gameplay input & simulation only here
    g.handle_input(dt);
    g.update(dt);
    if (g.lives <= 0) {
        StopMusicStream(g.music);
        g.high_score = std::max(g.high_score, g.score);
        g.state = GameState::GameOver;
    }
}

void updateGameOver(Game& g) {
    if (IsKeyPressed(KEY_ENTER)) {
        g.reset();
        PlayMusicStream(g.music);
        g.state = GameState::Playing;
    }
}

void drawFrameUI(Font font, Color grey, Color yellow) {
    ClearBackground(grey);
    DrawRectangleRoundedLinesEx({10,10,780,780}, 0.18f, 20, 2, yellow);
    DrawLineEx({25,730}, {775,730}, 3, yellow);
}

void drawHud(const Game& g, Font font, Color yellow, Texture2D ship_image) {
    // Level
    std::string level = std::string("LEVEL ") + format_level(g.level);
    DrawTextEx(font, level.c_str(), {565,740}, 34, 2, yellow);

    // Lives
    float x = 50.0f;
    for (int i = 0; i < g.lives; ++i) {
        DrawTextureV(ship_image, {x, 745}, WHITE);
        x += 50;
    }

    // Scores
    DrawTextEx(font, "SCORE", {50,15}, 34, 2, yellow);
    auto score_txt = format_trail_zeros(g.score, 5);
    DrawTextEx(font, score_txt.c_str(), {50,40}, 34, 2, yellow);

    DrawTextEx(font, "HIGH SCORE", {570,15}, 34, 2, yellow);
    auto high_txt = format_trail_zeros(g.high_score, 5);
    DrawTextEx(font, high_txt.c_str(), {655,40}, 34, 2, yellow);
}

int main() {
    // init window, audio, load assets...
    Game game;

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // --- Update: route by state ---
        switch (game.state) {
            case GameState::Title:   updateTitle(game); break;
            case GameState::Playing: updatePlaying(game, dt); break;
            case GameState::Paused:  /* updatePaused(game) */ break;
            case GameState::GameOver:updateGameOver(game); break;
        }

        // --- Draw: shared frame + per-state ---
        BeginDrawing();
            drawFrameUI(font, grey, yellow);

            switch (game.state) {
                case GameState::Title:
                    DrawTextEx(font, "PRESS ENTER TO START GAME", {290,740}, 34, 2, yellow);
                    // title art / logo...
                    break;

                case GameState::Playing:
                    drawHud(game, font, yellow, ship_image);
                    game.draw(); // draws world/entities
                    break;

                case GameState::Paused:
                    drawHud(game, font, yellow, ship_image);
                    DrawTextEx(font, "PAUSED", {600,740}, 34, 2, yellow);
                    break;

                case GameState::GameOver:
                    DrawTextEx(font, "GAME OVER", {565,740}, 34, 2, yellow);
                    DrawTextEx(font, "PRESS ENTER TO RESTART", {470, 700}, 24, 2, yellow);
                    break;
            }
        EndDrawing();
    }

    // teardown...
    CloseAudioDevice();
    CloseWindow();
}
