#include "lasers.hpp"

Laser::Laser(Vector2 position, int speed) {
    this -> position = position;
    this -> speed = speed;
}

void Laser::draw() {
    DrawRectangle(position.x, position.y, 4, 15, Color{0, 128, 0, 255});
}

void Laser::update() {
    position.y += speed;
}
