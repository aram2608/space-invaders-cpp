#include "aliens.hpp"

Alien::Alien(int type, Vector2 position) {
    this -> type = type;
    this -> position = position;

    // Match alien type to asset
    switch (type) {
    case 1:
        image = LoadTexture("assets/alien_1.png");
        break;
    case 2:
        image = LoadTexture("assets/alien_2.png");
        break;
    case 3:
        image = LoadTexture("assets/alien_3.png");
        break;
    default:
        image = LoadTexture("assets/alien_1.png");
        break;
    }
}

void Alien::draw() {
    DrawTexture(image, position.x, position.y, WHITE);
}

int Alien::get_type() {
    return type;
}