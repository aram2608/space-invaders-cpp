#pragma once
#include <raylib.h>

class Block {
public:
    Block(Vector2 position);
    void draw();
    Rectangle get_rect();

private:
    Vector2 position;
};