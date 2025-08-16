#pragma once
#include <vector>
#include "block.hpp"

class Obstacle {
public:
    Obstacle(Vector2 position);
    void draw();
    Vector2 position;
    std::vector<Block> blocks;
    // static allows us to use this attribute without creating an instance of Obstacle
    static std::vector<std::vector<int>> grid;
private:
};