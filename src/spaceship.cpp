#include "spaceship.hpp"

SpaceShip::SpaceShip() {
    image = LoadTexture("assets/spaceship.png");
    // Calculate starting point in middle of screen
    position.x = (GetScreenWidth() - image.width ) / 2;
    position.y = GetScreenHeight() - image.height;
    fire_time = 0;
}

SpaceShip::~SpaceShip() {
    UnloadTexture(image);
}

void SpaceShip::draw() {
    DrawTexture(image, position.x, position.y, WHITE);
}

void SpaceShip::move_left() {
    position.x -= 7;
    if (position.x < 0) {
        position.x = 0;
    }
}

void SpaceShip::move_right() {
    position.x += 7;
    if (position.x > GetScreenWidth() - image.width) {
        position.x = GetScreenWidth() - image.width;
    }
}

void SpaceShip::move_up() {
    position.y -= 7;
    if (position.y < 0) {
        position.y = 0;
    }
}

void SpaceShip::move_down() {
    position.y += 7;
    if (position.y > GetScreenHeight() - image.height) {
        position.y = GetScreenHeight() - image.height;
    }
}

void SpaceShip::fire_laser() {
    // Fires a laser with a wait time of 350 ms between shot
    if(GetTime() - fire_time >= 0.35) {
    lasers.push_back(Laser({position.x + image.width / 2 - 2, position.y},-6));
    fire_time = GetTime();
    }
}