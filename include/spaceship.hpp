#pragma once // instruction ensures that this header file is only used once
#include <raylib.h>

class SpaceShip {
    public:
        // Constructor
        SpaceShip();
        void draw();
        void move_left();
        void move_right();
        void fire_laser();
        // Deconstructor
        ~SpaceShip();

    private:
        // Data type to represent 2D images
        Texture2D image;
        // Data type that has both x and y pos
        Vector2 position;
};