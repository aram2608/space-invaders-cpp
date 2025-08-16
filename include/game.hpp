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
    std::vector<Alien> create_fleet();

    // Game assets
    SpaceShip ship;
    std::vector<Obstacle> obstacles;
    
    std::vector<Alien> aliens;
    int alien_dir;
    void move_aliens();
    void aliens_down(int distance);
    void aliens_shoot();
    std::vector<Laser> al_laser;
    // Constant expression for alien shot intervals, decided at compile time
    constexpr static float al_shot_intv = 0.35;
    float last_al_laser_time;
};