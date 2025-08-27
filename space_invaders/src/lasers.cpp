#include "lasers.hpp"

#include <iostream>

// Constructor - Laser - Takes Vector and int
Laser::Laser(Vector2 position, int speed) {
    this->position = position;
    this->speed    = speed;
    active         = true;
}

// Function to draw lasers to screen, handled with raylib
void Laser::draw() {
    // Draw a 4x15 green laser off the position of each instance of Laser
    if (active)
        DrawRectangle(position.x, position.y, 4, 15, Color{0, 128, 0, 255});
}

// Function to get rectangle for lasers
Rectangle Laser::get_rect() {
    Rectangle rect;
    rect.x = position.x, rect.y = position.y, rect.width = 4;
    rect.height = 15;
    return rect;
}

// Function to update laser position
void Laser::update() {
    position.y += speed;
    // Inactivates lasers given y_coords, catches both ship and alien lasers
    if (active) {
        if (position.y > GetScreenHeight() - 100 || position.y < 25) {
            active = false;
        }
    }
}
