#pragma once
#include "spaceship.hpp"
#include "lasers.hpp"

class Game {
    public:
        // Constructor
        Game();
        // Deconstructor
        ~Game();
    void draw();
    void update();
    void handle_input();
    private:
        SpaceShip ship;
};