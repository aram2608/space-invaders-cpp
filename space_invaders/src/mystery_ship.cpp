#include "mystery_ship.hpp"

// Constructor - MysteryShip
MysteryShip::MysteryShip() {
    image           = LoadTexture("assets/mystery.png");
    myst_ship_sound = LoadSound("audio/mystery_ship.ogg");
    alive           = false;
}

// Deconstructor - MysteryShip
MysteryShip::~MysteryShip() {
    UnloadTexture(image);
    UnloadSound(myst_ship_sound);
}

// Function to randomly spawn mystery ship at the top of the game window
void MysteryShip::spawn() {
    position.y = 90;
    int side   = GetRandomValue(0, 1);

    if (side == 0) {
        position.x = 25;
        speed      = 3;
    } else {
        position.x = GetScreenWidth() - image.width - 25;
        speed      = -3;
    }
    alive = true;
    PlaySound(myst_ship_sound);
}

// Function to get rectangle for mystery ship
Rectangle MysteryShip::get_rect() {
    // Only return rectangle if mystery ship is alive/on screen
    if (alive) {
        return {position.x, position.y, float(image.width), float(image.height)};
    } else {
        return {position.x, position.y, 0, 0};
    }
}

// Function to update mystery ship position
void MysteryShip::update() {
    if (alive) {
        position.x += speed;
        if (position.x > GetScreenWidth() - image.width - 25 || position.x < 25) {
            alive = false;
        }
    }
}

// Function to draw mystery ship to screen
void MysteryShip::draw() {
    if (alive) {
        DrawTextureV(image, position, WHITE);
    }
}