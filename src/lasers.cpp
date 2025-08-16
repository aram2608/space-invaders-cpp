#include "lasers.hpp"
#include <iostream>

Laser::Laser(Vector2 position, int speed) {
    this -> position = position;
    this -> speed = speed;
    active = true;
}

void Laser::draw() {
    // Draw a 4x15 green laser off the position
    if(active) DrawRectangle(position.x, position.y, 4, 15, Color{0, 128, 0, 255});
}

void Laser::update() {
    position.y += speed;
    if (active) {
        if (position.y > GetScreenHeight() || position.y < 0) {
            active = false;
        }
    }
}
