#include "spaceship.hpp"

SpaceShip::SpaceShip() {
    image = LoadTexture("assets/spaceship.png");
    position.x = 100;
    position.y = 100;
}

SpaceShip::~SpaceShip() {
    UnloadTexture(image);
}

void SpaceShip::draw() {
    DrawTexture(image, position, WHITE);
}