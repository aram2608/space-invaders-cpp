#include "ship/lasers.hpp"

#include <iostream>

// Constructor - Laser - Takes Vector and int
Laser::Laser(Vector2 position, int speed) {
    this->position_ = position;
    this->speed_ = speed;
    active_ = true;
}

// Function to draw lasers to screen, handled with raylib
void Laser::draw() {
    // Draw a 4x15 green laser off the position of each instance of Laser
    if (active_)
        DrawRectangle(position_.x, position_.y, 4, 15, Color{0, 128, 0, 255});
}

// Function to get rectangle for lasers
Rectangle Laser::get_rect() {
    Rectangle rect;
    rect.x = position_.x, rect.y = position_.y, rect.width = 4;
    rect.height = 15;
    return rect;
}

// Function to update laser position
void Laser::update(float &delta) {
    position_.y += speed_ * delta;
    // Inactivates lasers given y_coords, catches both ship and alien lasers
    if (active_) {
        if (position_.y > GetScreenHeight() - 100 || position_.y < 25) {
            active_ = false;
        }
    }
}
