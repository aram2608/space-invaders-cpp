#include "ui/ui.hpp"

#include "ui.hpp"

UI::UI() {
    font_ = LoadFontEx("font/monogram.ttf", 64, 0, 0);
    compute_cache();
    frame_ = Rectangle{10, 10, 780, 780};
    yellow_ = Color{243, 216, 63, 255};
    grey_ = Color{29, 29, 27, 255};
}

UI::~UI() { UnloadFont(font_); }

void UI::compute_cache() {
    title_ = MeasureTextEx(font_, "SPACE INVADERS", title_px_, spacing_);
    start_ = MeasureTextEx(font_, "RETURN TO START GAME", h2_px_, spacing_);
    high_ = MeasureTextEx(font_, "HIGH SCORE", h2_px_, spacing_);
    paused_ = MeasureTextEx(font_, "PAUSED", title_px_, spacing_);
    game_over_ = MeasureTextEx(font_, "GAME OVER", title_px_, spacing_);
    retry_ = MeasureTextEx(font_, "RETURN TO TRY AGAIN", h2_px_, spacing_);
}

void UI::draw_panel_background() {
    ClearBackground(grey_);
    DrawRectangleRoundedLinesEx(frame_, 0.18f, 20, 2, yellow_);
}

void UI::draw_hud(const Texture2D &ship, int lives) {
    DrawLineEx({25, 730}, {775, 730}, 3, yellow_);
    float x = 50.0;
    for (int i = 0; i < lives; i++) {
        DrawTextureV(ship, {x, 745}, WHITE);
        x += 50;
    }
}

void UI::draw_level_badge(std::string display, std::string level) {
    std::string out = display + " " + level;
    DrawTextEx(font_, out.c_str(), {565, 740}, 34, 2, yellow_);
}

void UI::draw_scoreboard(std::string score) {
    DrawTextEx(font_, "SCORE", {50, 15}, 34, 2, yellow_);
    DrawTextEx(font_, score.c_str(), {50, 40}, 34, 2, yellow_);
}

void UI::draw_scoreboard(std::string score, std::string high_score) {
    DrawTextEx(font_, "SCORE", {50, 15}, 34, 2, yellow_);
    DrawTextEx(font_, score.c_str(), {50, 40}, 34, 2, yellow_);

    DrawTextEx(font_, "HIGH SCORE", {570, 15}, 34, 2, yellow_);
    DrawTextEx(font_, high_score.c_str(), {655, 40}, 34, 2, yellow_);
}

void UI::draw_centered(const char *text, Vector2 center, Vector2 size, int px, float offset) {
    Vector2 pos{center.x - size.x * 0.5f, center.y - size.y * 0.5f + offset};
    DrawTextEx(font_, text, pos, px, spacing_, yellow_);
}

void UI::draw_game_over(Vector2 center) {
    DrawTextEx(font_, "GAME OVER",
               {center.x - game_over_.x / 2, (center.y - game_over_.y / 2) - 50}, 80, 2, yellow_);
    DrawTextEx(font_, "RETURN TO TRY AGAIN",
               {center.x - retry_.x / 2, (center.y - retry_.y / 2) + 20}, 34, 2, yellow_);
}
