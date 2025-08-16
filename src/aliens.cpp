#include "aliens.hpp"

// Store alien images into an array, improves loading time
Texture2D Alien::alien_images[3] = {};

// Function to unload textures after game ends, prevents mem leaks
void Alien::unload_images() {
    // Iterates over 
    for(int i = 0; i < 4; i++) {
        UnloadTexture(alien_images[i]);
    }
}

// Constructor
Alien::Alien(int type, Vector2 position) {
    this -> type = type;
    this -> position = position;

    // Load all of images into disc at once to speed up loading time
    if(alien_images[type -1].id == 0) {
        // Match alien type to asset
        switch (type) {
        case 1:
            alien_images[0] = LoadTexture("assets/alien_1.png");
            break;
        case 2:
            alien_images[1] = LoadTexture("assets/alien_2.png");
            break;
        case 3:
            alien_images[2] = LoadTexture("assets/alien_3.png");
            break;
        default:
            alien_images[0] = LoadTexture("assets/alien_1.png");
            break;
        }
    }
}

// Function to draw aliens to screen given a position in the vector
void Alien::draw() {
    DrawTexture(alien_images[type - 1], position.x, position.y, WHITE);
}

// Function to retrive alien type
int Alien::get_type() {
    return type;
}

// Function to update direction variable
void Alien::update(int direction) {
    position.x += direction;
}