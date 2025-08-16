#pragma once
#include <raylib.h>

class Block {
public:
    // Constructor
    Block(Vector2 position);
    void draw();
    Rectangle get_rect();

private:
    Vector2 position;
};