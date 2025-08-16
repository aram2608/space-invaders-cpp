#pragma once
#include "spaceship.hpp"
#include "obstacle.hpp"
#include "aliens.hpp"

class Game {
public:
    // Constructor - Game
    Game();
    // Deconstructor - Game
    ~Game();
    // Function to draw events onto game window
    void draw();
    // Function to update the events on screen
    void update();
    // Function to handle IO logic for game events
    void handle_input();

private:
    // Function to delete lasers to protect memory resources
    void delete_laser();
    // Function to return a vector of obstacles for the game window
    std::vector<Obstacle> make_obs();
    // Function to create a vector of aliens to spawn a fleet into game window
    std::vector<Alien> create_fleet();
    // Function to shift fleet position on game window
    void move_aliens();
    // Function to move entire fleet of aliens down the y direction
    void aliens_down(int distance);
    // Function handle firing logic for alien fleet
    void aliens_shoot();

    SpaceShip ship;
    std::vector<Obstacle> obstacles;
    std::vector<Alien> aliens;
    int alien_dir;
    std::vector<Laser> al_laser;
    constexpr static float al_shot_intv = 0.35;
    float last_al_laser_time;
};