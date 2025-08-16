#pragma once // instruction ensures that this header file is only used once
#include <raylib.h>
#include <vector>
#include "lasers.hpp"

class SpaceShip {
public:
    // Constructor - SpaceShip
    SpaceShip();
    // Function to draw ship to game window
    void draw();
    // Function to change x_coord left
    void move_left();
    // Function to change x_coord right
    void move_right();
    // Function to change y_coord up
    void move_up();
    // Function to change y_coord down
    void move_down();
    // Function to handle firing of ship laser
    void fire_laser();

    std::vector<Laser> lasers;

    // Deconstructor - SpaceShip
    ~SpaceShip();
private:
    Texture2D image;
    Vector2 position;
    double fire_time;
};