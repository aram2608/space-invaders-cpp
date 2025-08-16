#include "block.hpp"

// Constructor
Block::Block(Vector2 position) {
    this -> position = position;
}

// Function to draw Block instances, handled through raylib
void Block::draw() {
    DrawRectangle(position.x, position.y, 3, 3, {243, 216, 63, 255});
}

// Function to get rectangle for Block instances
Rectangle Block::get_rect() {
    Rectangle rect;
    rect.x = position.x;
    rect.y = position.y;
    rect.width = 3;
    rect.height = 3;
    return rect;
}