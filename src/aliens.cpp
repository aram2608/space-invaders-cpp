#include "aliens.hpp"

// Store alien images into an array
Texture2D Alien::alien_images[3] = {};

void Alien::unload_images() {
    for(int i = 0; i < 4; i++) {
        UnloadTexture(alien_images[i]);
    }
}

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

void Alien::draw() {
    DrawTexture(alien_images[type - 1], position.x, position.y, WHITE);
}

int Alien::get_type() {
    return type;
}

void Alien::update(int direction) {
    position.x += direction;
}