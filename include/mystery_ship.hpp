#pragma once
#include <raylib.h>

class MysteryShip {
    public:
        // Constructor - MysteryShip
        MysteryShip();
        // Deconstructor - MysteryShip
        ~MysteryShip();
        // Function to update mystery ship position
        void update();
        // Function to draw mystery ship to screen
        void draw();
        // Function to handle firing of ship laser
        void spawn();

        bool alive;
    private:
        Texture2D image;
        Vector2 position;
        int speed;
};