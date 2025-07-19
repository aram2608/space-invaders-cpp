// game.h
#ifndef GAME_H
#define GAME_H

#include <vector>
#include "buffer.h"
#include "sprite.h"
#include "texture.h"
#include <GLFW/glfw3.h>

class Game {
public:
    Game(size_t width, size_t height);
    ~Game();

    void update();
    void render();
    void handle_input(GLFWwindow* window);

private:
    void update_animation();
    void move_player();
    void draw_text();

    Buffer buffer;
    Texture texture;

    std::vector<Alien> aliens;
    std::vector<std::pair<size_t, size_t>> bullets;
    Player player;

    size_t player_x;
    size_t player_y;
    int player_move_dir;

    size_t anim_time = 0;

    Sprite alien_sprites[2];
    Sprite player_sprite;
    Sprite bullet_sprite;
    Sprite text_sprite;
};

#endif  // GAME_H