#include "game.hpp"
#include <iostream>

// Constructor - Game
Game::Game() {
    init();
}

// Deconstructor - Game
Game::~Game() {
    Alien::unload_images();
}

// Function to update the events on screen
void Game::update() {
    // Logic to handling spawn time of mystery ship
    double curr_t = GetTime();
    if(curr_t - lst_myst_spwn > myst_ship_intv) {
        mystery_ship.spawn();
        lst_myst_spwn = GetTime();
        myst_ship_intv = GetRandomValue(10, 20);
    }

    // Iterate over vector of lasers and update positions
    for(auto& laser: ship.lasers) {
        laser.update();
    }

    // Alien movement and logic
    move_aliens();
    aliens_shoot();

    // Update alien laser positions
    for(auto& laser: al_lasers) {
        laser.update();
    }

    // Clean up lasers that fly off screen
    delete_laser();
    mystery_ship.update();

    // Collision handling logic
    check_collisions();
}

// Function to draw events onto game window
void Game::draw() {
    ship.draw();
    mystery_ship.draw();

    // Iterate over vector of lasers and draw to screen
    for(auto& laser: ship.lasers) {
        laser.draw();
    }

    // Iterate over vector of obstacles and draw to screen
    for(auto& obs: obstacles) {
        obs.draw();
    }

    // Iterate over a vector of aliens and draw to screen
    for(auto& alien: aliens) {
        alien.draw();
    }

    // Iterate over a vector of alien lasers and draw to screen
    for(auto& laser: al_lasers) {
        laser.draw();
    }
}

// Function to delete lasers to protect memory resources
void Game::delete_laser() {
    // Iterator to loop through the vector and remove any inactive ship lasers
    for(auto it = ship.lasers.begin(); it != ship.lasers.end();) {
        if(!it -> active) {
            it = ship.lasers.erase(it);
        } else {
            ++ it;
        }
    }

    // Iterator to loop through the vector and remove any inactive alien lasers
    for(auto it = al_lasers.begin(); it != al_lasers.end();) {
        if(!it -> active) {
            it = al_lasers.erase(it);
        } else {
            ++ it;
        }
    }
}

// Function to return a vector of obstacles for the game window
std::vector<Obstacle> Game::make_obs() {
    // Calculate obstacle width and gaps between obstacles
    int obs_w = Obstacle::grid[0].size() * 3;
    float obs_gap = (GetScreenWidth() - (4 * obs_w)) / 5;

    // Iterate over the number of obstacles we want to make (4)
    for(int i = 0; i < 4; i++) {
        float off_x = (i + 1) * obs_gap + i * obs_w;
        obstacles.push_back(Obstacle({off_x, float(GetScreenHeight() - 100)}));
    }
    return obstacles;
}

// Function to create a vector of aliens to spawn a fleet into game window
std::vector<Alien> Game::create_fleet() {
    std::vector<Alien> aliens;
    // Iterate over a 5 row x 11 column grid to create a fleet of 55 aliens
    for(int row = 0; row < 5; row++) {
        for(int column = 0; column < 11; column++) {

            // Calculates alien type from row number
            int alien_t;
            if(row == 0) {
                alien_t = 3;
            } else if(row == 1 || row == 2) {
                alien_t = 2;
            } else {
                alien_t = 1;
            }
            
            // Calculate x and y by an arbitrary cell_size of 55
            float x = 75 + column * 55;
            float y = 100 + row * 55;
            aliens.push_back(Alien(alien_t, {x, y}));
        }
    }
    return aliens;
}

// Function to handle IO logic for game events
void Game::handle_input() {
    if(IsKeyDown(KEY_LEFT)) {
        ship.move_left();
    } else if (IsKeyDown(KEY_RIGHT)) {
        ship.move_right();
    } else if (IsKeyDown(KEY_UP)) {
        ship.move_up();
    } else if (IsKeyDown(KEY_DOWN)) {
        ship.move_down();
    } else if (IsKeyDown(KEY_SPACE)) {
        ship.fire_laser();
    }
}

// Function to shift fleet position on game window
void Game::move_aliens() {
    // Calculate screen position to make sure the aliens stay on screen
    // Move aliens down once the edge of screen is met
    for(auto& alien: aliens) {
        // Right side of screen
        if(alien.position.x + alien.alien_images[alien.type - 1].width > GetScreenWidth()) {
            alien_dir = -1;
            aliens_down(4);
        }
        // Left side of screen
        if(alien.position.x < 0) {
            alien_dir = 1;
            aliens_down(4);
        }
        // Update movement
        alien.update(alien_dir);
    }
}

// Function to move entire fleet of aliens down the y direction
void Game::aliens_down(int distance) {
    // Iterate over vector of aliens and update y_coord for each alien
    for(auto& alien: aliens) {
        alien.position.y += distance;
    }
}

// Function handle firing logic for alien fleet
void Game::aliens_shoot() {
    // Get time and if current time is greq to interval and aliens are on screen fire
    double curr_time = GetTime();
    if(curr_time - last_al_laser_time >= al_shot_intv && !aliens.empty()) {

        // Pick a random alien and have it fire a laser
        int rand_idx = GetRandomValue(0, aliens.size() - 1);
        Alien& alien = aliens[rand_idx];

        // Vector {x_coord, y_coord} calculations with a laser speed of 6 pixels
        al_lasers.push_back(Laser(
            {alien.position.x + alien.alien_images[alien.type - 1].width / 2, 
            alien.position.y + alien.alien_images[alien.type - 1].height}, 6)
        );

        // Update last fire time given completion of previous code
        last_al_laser_time = GetTime();
    }
}

// Function to handle collisions
void Game::check_collisions() {
    // Spaceship Lasers
    for(auto& laser: ship.lasers) {
        // Iterate over aliens in alien vector and check for collisions
        auto it = aliens.begin();
        while(it != aliens.end()) {
            if(CheckCollisionRecs(it -> get_rect(), laser.get_rect())) {
                it = aliens.erase(it);
                laser.active = false;
            } else {
                ++it;
            }
        }
        // Iterate over obstacles vector to check for collisions
        for(auto& obs: obstacles) {
            auto it = obs.blocks.begin();
            while(it != obs.blocks.end()) {
                if(CheckCollisionRecs(it -> get_rect(), laser.get_rect())) {
                    it = obs.blocks.erase(it);
                    laser.active = false;
                } else {
                    ++it;
                }
            }
        }
        // Check laser/mystery ship collisions
        if(CheckCollisionRecs(laser.get_rect(), mystery_ship.get_rect())) {
            laser.active = false;
            mystery_ship.alive = false;
        }
    }
    // Alien lasers
    for(auto& laser: al_lasers) {
        // Check for ship/laser collisions
        if(CheckCollisionRecs(laser.get_rect(), ship.get_rect())) {
            laser.active = false;
            lives -= 1;
            std::cout << "Ship Hit!" << lives << std::endl;
        }
        // Iterate over obstacles vector to check for collisions
        for(auto& obs: obstacles) {
            auto it = obs.blocks.begin();
            while(it != obs.blocks.end()) {
                if(CheckCollisionRecs(it -> get_rect(), laser.get_rect())) {
                    it = obs.blocks.erase(it);
                    laser.active = false;
                } else {
                    ++it;
                }
            }
        }
    }
}

// Function to initialize game parameters
void Game::init() {
    obstacles = make_obs();
    aliens = create_fleet();
    alien_dir = 1;
    last_al_laser_time = 0.0;
    lst_myst_spwn = 0.0;
    myst_ship_intv = GetRandomValue(10, 20);
    lives = 3;
}
