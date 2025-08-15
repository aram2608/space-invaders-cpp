#include "spaceship.hpp"

SpaceShip::SpaceShip() {
    image = LoadTexture("assets/spaceship.png");
    // Calculate starting point in middle of screen
    position.x = (GetScreenWidth() - image.width ) / 2;
    position.y = GetScreenHeight() - image.height;
}

SpaceShip::~SpaceShip() {
    UnloadTexture(image);
}

void SpaceShip::draw() {
    DrawTexture(image, position.x, position.y, WHITE);
}

void SpaceShip::move_left() {
    position.x -= 7;
}

void SpaceShip::move_right() {
    position.x += 7;
}

void SpaceShip::move_up() {
    position.y -= 7;
}

void SpaceShip::move_down() {
    position.y += 7;
}