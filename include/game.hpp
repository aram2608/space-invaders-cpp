#pragma once
#include "spaceship.hpp"
#include "obstacle.hpp"
#include "aliens.hpp"
#include "mystery_ship.hpp"

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

    int lives;
    bool run;
    int score;
    int high_score;
    int level;
    int new_game;
    Music music;
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
    // Function to handle collisions
    void check_collisions();
    // Function to initialize game parameters
    void init();
    // Function to reset game after game over
    void reset();
    // Function to terminate game when lives reach zero
    void game_over();
    // Function to update high score
    void score_check();
    // Function to save high score to a text file
    void save_high_scr(int high_scr);
    // Function to load a high score at start of game from text file
    int load_score_file();
    // Function to progress to new level
    std::vector<Alien> new_level();

    SpaceShip ship;
    std::vector<Obstacle> obstacles;
    std::vector<Alien> aliens;
    MysteryShip mystery_ship;
    int alien_dir;
    std::vector<Laser> al_lasers;
    constexpr static float al_shot_intv = 0.35;
    float last_al_laser_time;
    float myst_ship_intv;
    float lst_myst_spwn;
    Sound explosion_sound;
    Sound game_over_sound;
};