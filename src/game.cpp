#include "game.h"
#include <iostream>
#include <algorithm>

// Constructor: Set up buffer, sprites, player, aliens, bullets
Game::Game(size_t width, size_t height)
    : buffer(width, height),
    texture(width, height, buffer.data),
    // Alien sprites: two animation frames
    alien_sprites{
        Sprite(11, 8, new uint8_t[88]{
            // Alien frame 1
            0,0,1,0,0,0,0,0,1,0,0,
            0,0,0,1,0,0,0,1,0,0,0,
            0,0,1,1,1,1,1,1,1,0,0,
            0,1,1,0,1,1,1,0,1,1,0,
            1,1,1,1,1,1,1,1,1,1,1,
            1,0,1,1,1,1,1,1,1,0,1,
            1,0,1,0,0,0,0,0,1,0,1,
            0,0,0,1,1,0,1,1,0,0,0}),
        Sprite(11, 8, new uint8_t[88]{
            // Alien frame 2
            0,0,1,0,0,0,0,0,1,0,0,
            1,0,0,1,0,0,0,1,0,0,1,
            1,0,1,1,1,1,1,1,1,0,1,
            1,1,1,0,1,1,1,0,1,1,1,
            1,1,1,1,1,1,1,1,1,1,1,
            0,1,1,1,1,1,1,1,1,1,0,
            0,0,1,0,0,0,0,0,1,0,0,
            0,1,0,0,0,0,0,0,0,1,0})
    },
    // Player ship sprite
    player_sprite(Sprite(11, 7, new uint8_t[77]{
        0,0,0,0,0,1,0,0,0,0,0,
        0,0,0,0,1,1,1,0,0,0,0,
        0,0,0,0,1,1,1,0,0,0,0,
        0,1,1,1,1,1,1,1,1,1,0,
        1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1}))
    // Bullet sprite (thin vertical line)
    bullet_sprite(Sprite(1, 3, new uint8_t[3]{1, 1, 1})) 
{
    // Initialize alien positions in grid
    const size_t num_rows = 5;
    const size_t num_cols = 11;
    const size_t alien_spacing_x = 16;
    const size_t alien_spacing_y = 17;

    for (size_t row = 0; row < num_rows; ++row) {
        for (size_t col = 0; col < num_cols; ++col) {
            size_t x = col * alien_spacing_x + 20;
            size_t y = row * alien_spacing_y + 128;
            aliens.emplace_back(Alien());  // Push back empty alien for now
            aliens.back().draw_to(buffer, x, y, rgb_to_uint32(128, 0, 0));  // Draw red alien
        }
    }

    // Initialize player
    player = Player();
    player_x = 112 - 5;
    player_y = 32;
    player_move_dir = 1;
}

Game::~Game() = default;

// Update positions, animation, bullets
void Game::update() {
    update_animation();

    // Move bullets upward
    for (auto& bullet : bullets) {
        bullet.second += 4;
    }

    // Remove bullets that are offscreen
    bullets.erase(
        std::remove_if(bullets.begin(), bullets.end(),
                    [&](const auto& b) {
                        return b.second > buffer.height;
                    }),
        bullets.end());
}

// Flip Y to match OpenGL origin
inline size_t flip_y(const Buffer& buffer, size_t y, size_t h) {
    return buffer.height - y - h;
}

// Draw all game elements
void Game::render() {
    buffer.clear(rgb_to_uint32(0, 128, 0));  // Green background

    size_t current_frame = (anim_time / 10) % 2;

    // Draw aliens
    for (size_t i = 0; i < aliens.size(); ++i) {
        size_t x = 20 + (i % 11) * 16;
        size_t y = 128 + (i / 11) * 17;
        size_t y_flipped = flip_y(buffer, y, alien_sprites[current_frame].get_height());

        alien_sprites[current_frame].draw_to(buffer, x, y_flipped, rgb_to_uint32(128, 0, 0));
    }

    // Draw player
    size_t player_y_flipped = flip_y(buffer, player_y, player_sprite.get_height());
    player.draw_to(buffer, player_x, player_y_flipped, rgb_to_uint32(0, 0, 250));

    // Draw bullets
    for (const auto& bullet : bullets) {
        size_t bullet_y_flipped = flip_y(buffer, bullet.second, bullet_sprite.get_height());
        bullet_sprite.draw_to(buffer, bullet.first, bullet_y_flipped, rgb_to_uint32(255, 255, 255));
    }

    // Draw static score text
    draw_text();

    // Send final buffer to GPU
    texture.update(buffer);
}

// Handle player input
void Game::handle_input(GLFWwindow* window) {
    const int speed = 2;

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && player_x > 0) {
        player_x -= speed;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && player_x + player.get_width() < buffer.width) {
        player_x += speed;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        size_t bullet_x = player_x + player.get_width() / 2;
        size_t bullet_y = player_y + player_sprite.get_height();
        bullets.emplace_back(bullet_x, bullet_y);
    }
}

// Animate alien sprite frames
void Game::update_animation() {
    ++anim_time;
    if (anim_time >= 20) anim_time = 0;
}

// Render a single 5x7 character from sprite sheet
void draw_char(Buffer& buffer, const Sprite& font, char c, size_t x, size_t y, uint32_t color) {
    if (c < 32 || c > 126) return;  // Skip non-printable
    size_t index = (c - 32) * 5;

    for (size_t row = 0; row < 7; ++row) {
        for (size_t col = 0; col < 5; ++col) {
            size_t offset = row * 35 + index + col;
            if (font.get_data()[offset]) {
                if (x + col < buffer.width && y + row < buffer.height) {
                    buffer.data[(y + row) * buffer.width + (x + col)] = color;
                }
            }
        }
    }
}

// Draw static HUD text
void Game::draw_text() {
    const char* msg = "SCORE: 1337";
    size_t x = 4;
    size_t y = 4;

    for (size_t i = 0; msg[i] != '\0'; ++i) {
        draw_char(buffer, text_sprite, msg[i], x + i * 6, y, rgb_to_uint32(255, 255, 255));
    }
}