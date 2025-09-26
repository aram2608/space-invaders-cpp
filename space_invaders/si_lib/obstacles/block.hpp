#pragma once
#include <raylib.h>

class Block {
  public:
    // Constructor - Block - Takes Vector2
    Block(Vector2 position);
    // Function to draw Block instances, handled through raylib
    void draw();
    // Function to get rectangle for Block instances
    Rectangle get_rect();

  private:
    Vector2 position;
};