#include "aliens.hpp"

Texture2D Alien::alien_images[3] = {}; 

Alien::Alien(int type, Vector2 position) {
    this -> type = type;
    this -> position = position;

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