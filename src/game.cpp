// game.cpp
#include "game.h"
#include <iostream>

// Constructor: initializes game state, player, aliens, sprites, and buffer
Game::Game(size_t width, size_t height)
    : buffer(width, height),
    texture(width, height, buffer.data),
    alien_sprites {
        Sprite(11, 8, new uint8_t[88] {
            0,0,1,0,0,0,0,0,1,0,0,
            0,0,0,1,0,0,0,1,0,0,0,
            0,0,1,1,1,1,1,1,1,0,0,
            0,1,1,0,1,1,1,0,1,1,0,
            1,1,1,1,1,1,1,1,1,1,1,
            1,0,1,1,1,1,1,1,1,0,1,
            1,0,1,0,0,0,0,0,1,0,1,
            0,0,0,1,1,0,1,1,0,0,0
        }),
        Sprite(11, 8, new uint8_t[88] {
            0,0,1,0,0,0,0,0,1,0,0,
            1,0,0,1,0,0,0,1,0,0,1,
            1,0,1,1,1,1,1,1,1,0,1,
            1,1,1,0,1,1,1,0,1,1,1,
            1,1,1,1,1,1,1,1,1,1,1,
            0,1,1,1,1,1,1,1,1,1,0,
            0,0,1,0,0,0,0,0,1,0,0,
            0,1,0,0,0,0,0,0,0,1,0
        })
    },
    player_sprite(11, 7, new uint8_t[77] {
        0,0,0,0,0,1,0,0,0,0,0,
        0,0,0,0,1,1,1,0,0,0,0,
        0,0,0,0,1,1,1,0,0,0,0,
        0,1,1,1,1,1,1,1,1,1,0,
        1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1
    })
{

    // Initialize player sprite
    player_sprite = Sprite(11, 7, new uint8_t[77] {
        0,0,0,0,0,1,0,0,0,0,0,
        0,0,0,0,1,1,1,0,0,0,0,
        0,0,0,0,1,1,1,0,0,0,0,
        0,1,1,1,1,1,1,1,1,1,0,
        1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1
    });

    // Initialize aliens
    const size_t num_rows = 5;
    const size_t num_cols = 11;
    const size_t alien_spacing_x = 16;
    const size_t alien_spacing_y = 17;

    for (size_t row = 0; row < num_rows; ++row) {
        for (size_t col = 0; col < num_cols; ++col) {
            size_t x = col * alien_spacing_x + 20;
            size_t y = row * alien_spacing_y + 128;
            aliens.emplace_back(Alien());  // use default Alien constructor
            aliens.back().draw_to(buffer, x, y, rgb_to_uint32(128, 0, 0)); // preview
        }
    }

    // Position player
    player = Player();
    player_move_dir = 1;
    player_x = 112 - 5;
    player_y = 32;
}

// Destructor: no explicit cleanup needed since buffer/texture handle their own memory
Game::~Game() = default;

// Called every frame to update game state (e.g., animation timing, player movement)
void Game::update() {
    update_animation();
    move_player();
}

// Draw all game elements to the buffer and upload to GPU texture
void Game::render() {
    buffer.clear(rgb_to_uint32(0, 128, 0));  // clear to green

    // Flip helper
    auto flip_y = [&](size_t y, size_t h) {
        return buffer.height - y - h;
    };

    // Draw aliens using current animation frame
    size_t current_frame = (anim_time / 10) % 2;
    for (size_t i = 0; i < aliens.size(); ++i) {
        const Alien& alien = aliens[i];
        size_t x = 20 + (i % 11) * 16;
        size_t y = 128 + (i / 11) * 17;
        size_t flipped_y = flip_y(y, alien_sprites[current_frame].get_height());

        alien_sprites[current_frame].draw_to(buffer, x, flipped_y, rgb_to_uint32(128, 0, 0));
    }

    // Draw player
    size_t flipped_player_y = flip_y(player_y, player_sprite.get_height());
    player.draw_to(buffer, player_x, flipped_player_y, rgb_to_uint32(0, 0, 250));

    // Upload frame to GPU
    texture.update(buffer);
}

// Advance animation frame counter
void Game::update_animation() {
    ++anim_time;
    if (anim_time >= 20) anim_time = 0;
}

// Moves player left/right and bounces when reaching edge
void Game::move_player() {
    const int step = 1;
    const size_t sprite_width = player_sprite.get_width();

    if (player_x + sprite_width + player_move_dir >= buffer.width) {
        player_x = buffer.width - sprite_width - 1;
        player_move_dir *= -1;
    } else if ((int)player_x + player_move_dir <= 0) {
        player_x = 0;
        player_move_dir *= -1;
    } else {
        player_x += player_move_dir;
    }
}
