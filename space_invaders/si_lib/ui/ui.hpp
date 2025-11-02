#pragma once

#include <raylib.h>
#include <string>

struct UI {
    UI();
    ~UI();
    void compute_cache();
    void compute_high();
    void draw_panel_background();
    void draw_hud(const Texture2D &ship, int lives);
    void draw_level_badge(std::string display, std::string level);
    void draw_scoreboard(std::string score);
    void draw_scoreboard(std::string score, std::string high_score);
    void draw_centered(const char *text, Vector2 center, Vector2 size, int px, float offset);
    void draw_game_over(Vector2 center);
    Vector2 title_;
    Vector2 start_;
    Vector2 high_;
    Vector2 paused_;
    Vector2 game_over_;
    Vector2 retry_;
    Font font_;
    Rectangle frame_;
    Color yellow_;
    Color grey_;

    bool cache_ok_{false};
    int title_px_ = 80;
    int h2_px_ = 34;
    float spacing_ = 2.f;
};