#pragma once
#include "spaceship.hpp"
#include "obstacle.hpp"
#include "aliens.hpp"
#include "mystery_ship.hpp"

// Enum class to handle game states
enum class GameState { Title, Playing, Paused, GameOver };

class Game {
public:
    // Constructor - Game
    Game();
    // Deconstructor - Game
    ~Game();
    // Function to draw events onto game window
    void draw();
    // Function to draw the title screen
    void draw_title();
    // Function to draw the paused screen
    void draw_paused();
    // Function to draw the game over screen
    void draw_gameover();
    // Function to draw the playing screen
    void draw_playing();

    // Function to update the events on screen
    void update();
    // Function to handle IO logic for game events
    void handle_input();
    // Function to handle title game state
    void update_title();
    // Function to handle playing game state
    void update_playing();
    // Function to handle gameover state
    void update_gameover();
    // Function to handle paused stated
    void update_paused();

    int lives;
    int score;
    int high_score;
    int level;

    GameState state = GameState::Title;
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
    // Function to check the current level
    std::vector<Alien> check_level();
    // Function to format the scores
    std::string format_trail_zeros(int number, int width);
    // Function to reformat level displayed on UI
    std::string format_level(int number);

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

    // UI component measurements
    Texture2D ship_image;
    Font font;
    Vector2 high_scr_title_size;
    Vector2 title_size;
    Vector2 game_over_title_size;
    Vector2 retry_text_size;
    Vector2 start_text_size;
    Vector2 gameover_scr_size;
    Vector2 screen_center;
    Vector2 paused_txt;
    Color grey;
    std::string level_display;
    Color yellow;
};