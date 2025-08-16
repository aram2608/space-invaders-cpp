#pragma once
#include <raylib.h>

class Laser {
public:
    // Constructor - Laser - Takes Vector and int
    Laser(Vector2 position, int speed);
    // Function to update laser position
    void update();
    // Function to draw lasers to screen, handled with raylib
    void draw();

    bool active;
private:
    Vector2 position;
    int speed;
};