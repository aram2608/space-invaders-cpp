#include "mystery_ship.hpp"

// Constructor - MysteryShip
MysteryShip::MysteryShip() {
    image = LoadTexture("assets/mystery.png");
    alive = false;
}

// Deconstructor - MysteryShip
MysteryShip::~MysteryShip() {
    UnloadTexture(image);
}

// Function to randomly spawn mystery ship at the top of the game window
void MysteryShip::spawn() {
    position.y = 90;
    int side = GetRandomValue(0, 1);

    if(side == 0) {
        position.x = 0;
        speed = 3;
    } else {
        position.x = GetScreenWidth() - image.width;
        speed = -3;
    }
    alive = true;
}

// Function to update mystery ship position
void MysteryShip::update() {
    if(alive) {
        position.x += speed;
        if(position.x > GetScreenWidth() - image.width || position.x < 0) {
            alive = false;
        }
    }
}

// Function to draw mystery ship to screen
void MysteryShip::draw() {
    if(alive) {
        DrawTextureV(image, position, WHITE);
    }
}