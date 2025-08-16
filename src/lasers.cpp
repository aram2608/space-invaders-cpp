#include "lasers.hpp"
#include <iostream>

// Constructor
Laser::Laser(Vector2 position, int speed) {
    this -> position = position;
    this -> speed = speed;
    active = true;
}

// Function to draw lasers to screen, handled with raylib
void Laser::draw() {
    // Draw a 4x15 green laser off the position of each instance of Laser
    if(active) DrawRectangle(position.x, position.y, 4, 15, Color{0, 128, 0, 255});
}

// Function to update laser position
void Laser::update() {
    position.y += speed;
    // Inactivates lasers given y_coords, catches both ship and alien lasers
    if (active) {
        if (position.y > GetScreenHeight() || position.y < 0) {
            active = false;
        }
    }
}
