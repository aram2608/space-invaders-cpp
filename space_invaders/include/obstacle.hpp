#pragma once
#include "block.hpp"

#include <vector>

class Obstacle {
  public:
    // Constructor - Obstacle - Takes a Vector2
    Obstacle(Vector2 position);
    // Function to draw obstacles onto screen
    void draw();

    Vector2                              position;
    std::vector<Block>                   blocks;
    static std::vector<std::vector<int>> grid;

  private:
};