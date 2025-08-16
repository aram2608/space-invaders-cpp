#pragma once // instruction ensures that this header file is only used once
#include <raylib.h>
#include "lasers.hpp"
#include <vector>

class SpaceShip {
    public:
        // Constructor
        SpaceShip();
        void draw();
        void move_left();
        void move_right();
        void move_up();
        void move_down();
        void fire_laser();
        std::vector<Laser> lasers;
        // Deconstructor
        ~SpaceShip();

    private:
        // Data type to represent 2D images
        Texture2D image;
        // Data type that has both x and y pos
        Vector2 position;
        // Keeps track of fire rate
        double fire_time;
};