#include "ship/spaceship.hpp"

// Constructor - SpaceShip
SpaceShip::SpaceShip() {
    image_ = LoadTexture("assets/spaceship.png");
    laser_sound_ = LoadSound("audio/player_laser.ogg");
    // Calculate starting point in middle of screen
    position_.x = (GetScreenWidth() - image_.width) / 2;
    position_.y = GetScreenHeight() - image_.height - 100;
    fire_time_ = 0;
    speed_ = 400;
}

// Destructor - SpaceShip
SpaceShip::~SpaceShip() {
    UnloadTexture(image_);
    UnloadSound(laser_sound_);
}

// Function to draw ship to game window
void SpaceShip::draw() { DrawTexture(image_, position_.x, position_.y, WHITE); }

// Function to change x_coord left
void SpaceShip::move_left(float delta) {
    position_.x -= speed_ * delta;
    if (position_.x < 25) {
        position_.x = 25;
    }
}

// Function to change x_coord right
void SpaceShip::move_right(float delta) {
    position_.x += speed_ * delta;
    if (position_.x > GetScreenWidth() - image_.width - 25) {
        position_.x = GetScreenWidth() - image_.width - 25;
    }
}

// Function to handle firing of ship laser
void SpaceShip::fire_laser() {
    // Fires a laser with a wait time of 350 ms between shot
    if (GetTime() - fire_time_ >= 0.35) {
        // We create the laser in place and stuff it into the vector
        lasers.emplace_back(Vector2{position_.x + image_.width / 2 - 2, position_.y}, -300);
        // We then reset the fire time
        fire_time_ = GetTime();
        PlaySound(laser_sound_);
    }
}

// Function to get rectangle for ship
Rectangle SpaceShip::get_rect() {
    return {position_.x, position_.y, float(image_.width), float(image_.height)};
}

// Function to reset spaceship
void SpaceShip::reset() {
    position_.x = (GetScreenWidth() - image_.width) / 2;
    position_.y = GetScreenHeight() - image_.height - 100;
    lasers.clear();
}