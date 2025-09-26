#include "ship/spaceship.hpp"

// Constructor - SpaceShip
SpaceShip::SpaceShip() {
    image       = LoadTexture("assets/spaceship.png");
    laser_sound = LoadSound("audio/player_laser.ogg");
    // Calculate starting point in middle of screen
    position.x = (GetScreenWidth() - image.width) / 2;
    position.y = GetScreenHeight() - image.height - 100;
    fire_time  = 0;
}

// Destructor - SpaceShip
SpaceShip::~SpaceShip() {
    UnloadTexture(image);
    UnloadSound(laser_sound);
}

// Function to draw ship to game window
void SpaceShip::draw() {
    DrawTexture(image, position.x, position.y, WHITE);
}

// Function to change x_coord left
void SpaceShip::move_left() {
    position.x -= 7;
    if (position.x < 25) {
        position.x = 25;
    }
}

// Function to change x_coord right
void SpaceShip::move_right() {
    position.x += 7;
    if (position.x > GetScreenWidth() - image.width - 25) {
        position.x = GetScreenWidth() - image.width - 25;
    }
}

// Function to change y_coord up
void SpaceShip::move_up() {
    position.y -= 7;
    if (position.y < 0 + 25) {
        position.y = 0 + 25;
    }
}

// Function to change y_coord down
void SpaceShip::move_down() {
    position.y += 7;
    if (position.y > GetScreenHeight() - image.height - 100) {
        position.y = GetScreenHeight() - image.height - 100;
    }
}

// Function to handle firing of ship laser
void SpaceShip::fire_laser() {
    // Fires a laser with a wait time of 350 ms between shot
    if (GetTime() - fire_time >= 0.35) {
        lasers.push_back(Laser({position.x + image.width / 2 - 2, position.y}, -6));
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