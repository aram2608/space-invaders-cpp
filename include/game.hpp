#pragma once
#include "spaceship.hpp"
#include "obstacle.hpp"

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
    std::vector<Obstacle> make_obs();
    SpaceShip ship;
    std::vector<Obstacle> obstacles;
};