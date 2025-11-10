#include "aliens/aliens.hpp"

// Store alien images into an array, improves loading time
Texture2D Alien::alien_images_[3] = {};

// Function to unload textures after game ends, prevents mem leaks
void Alien::unload_images() {
    // Iterates over
    for (int it = 0; it < 4; it++) {
        UnloadTexture(alien_images_[it]);
    }
}

// Function to get rectangle for aliens
Rectangle Alien::get_rect() {
    return {position_.x, position_.y, float(alien_images_[type_ - 1].width),
            float(alien_images_[type_ - 1].height)};
}

// Constructor - Alien - Takes int and Vector2
Alien::Alien(int type, Vector2 position) {
    this->type_ = type;
    this->position_ = position;

    // Load all of images into disc at once to speed up loading time
    if (alien_images_[type_ - 1].id == 0) {
        // Match alien type to asset
        switch (type) {
        case 1:
            alien_images_[0] = LoadTexture("assets/alien_1.png");
            break;
        case 2:
            alien_images_[1] = LoadTexture("assets/alien_2.png");
            break;
        case 3:
            alien_images_[2] = LoadTexture("assets/alien_3.png");
            break;
        default:
            alien_images_[0] = LoadTexture("assets/alien_1.png");
            break;
        }
    }
}

// Function to draw aliens to screen given a position in the vector
void Alien::draw() { DrawTexture(alien_images_[type_ - 1], position_.x, position_.y, WHITE); }

// Function to retrive alien type
int Alien::get_type() { return type_; }

// Function to update direction variable
void Alien::update(int direction) { position_.x += direction; }