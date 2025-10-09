#include "ship/spaceship.hpp"

// Constructor - SpaceShip
SpaceShip::SpaceShip() {
    image = LoadTexture("assets/spaceship.png");
    laser_sound = LoadSound("audio/player_laser.ogg");
    // Calculate starting point in middle of screen
    position.x = (GetScreenWidth() - image.width) / 2;
    position.y = GetScreenHeight() - image.height - 100;
    fire_time = 0;
    speed = 400;
}

// Destructor - SpaceShip
SpaceShip::~SpaceShip() {
    UnloadTexture(image);
    UnloadSound(laser_sound);
}

// Function to draw ship to game window
void SpaceShip::draw() { DrawTexture(image, position.x, position.y, WHITE); }

// Function to change x_coord left
void SpaceShip::move_left(float delta) {
    position.x -= speed * delta;
    if (position.x < 25) {
        position.x = 25;
    }
}

// Function to change x_coord right
void SpaceShip::move_right(float delta) {
    position.x += speed * delta;
    if (position.x > GetScreenWidth() - image.width - 25) {
        position.x = GetScreenWidth() - image.width - 25;
    }
}

// Function to handle firing of ship laser
void SpaceShip::fire_laser() {
    // Fires a laser with a wait time of 350 ms between shot
    if (GetTime() - fire_time >= 0.35) {
        // We create the laser in place and stuff it into the vector
        lasers.emplace_back(Vector2{position.x + image.width / 2 - 2, position.y}, -300);
        // We then reset the fire time
        fire_time = GetTime();
        PlaySound(laser_sound);
    }
}

// Function to get rectangle for ship
Rectangle SpaceShip::get_rect() {
    return {position.x, position.y, float(image.width), float(image.height)};
}

// Function to reset spaceship
void SpaceShip::reset() {
    position.x = (GetScreenWidth() - image.width) / 2;
    position.y = GetScreenHeight() - image.height - 100;
    lasers.clear();
}