#pragma once
#include "spaceship.hpp"
#include "obstacle.hpp"
#include "aliens.hpp"

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
    void delete_laser();
    // Helper functions to create assets
    std::vector<Obstacle> make_obs();
    std::vector<Alien> make_alien();

    // Game assets
    SpaceShip ship;
    std::vector<Obstacle> obstacles;
    std::vector<Alien> aliens;
};