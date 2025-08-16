#include "game.hpp"
#include <iostream>

// Constructor
Game::Game() {
    obstacles = make_obs();
    aliens = make_alien();
    alien_dir = 1;
    last_al_laser_time = 0.0;
}

// Deconstructor
Game::~Game() {
    Alien::unload_images();
}

void Game::update() {
    // Iterate over vector of lasers and update positions
    for(auto& laser: ship.lasers) {
        laser.update();
    }

    // Alien movement and logic
    move_aliens();
    aliens_shoot();

    // Update alien laser positions
    for(auto& laser: al_laser) {
        laser.update();
    }

    // Clean up lasers that fly off screen
    delete_laser();
}

void Game::draw() {
    ship.draw();

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
    for(auto& laser: al_laser) {
        laser.draw();
    }
}

void Game::delete_laser() {
    // Iterator to loop through the vector and remove any inactive lasers
    for(auto it = ship.lasers.begin(); it != ship.lasers.end();) {
        if(!it -> active) {
            it = ship.lasers.erase(it);
        } else {
            ++ it;
        }
    }
}

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

std::vector<Alien> Game::make_alien() {
    std::vector<Alien> aliens;
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

void Game::move_aliens() {
    // Calculate screen position to make sure the aliens stay on screen
    // Move aliens down once the edge of screen is met
    for(auto& alien: aliens) {
        if(alien.position.x + alien.alien_images[alien.type - 1].width > GetScreenWidth()) {
            alien_dir = -1;
            aliens_down(4);
        }
        if(alien.position.x < 0) {
            alien_dir = 1;
            aliens_down(4);
        }
        // Update movement
        alien.update(alien_dir);
    }
}

void Game::aliens_down(int distance) {
    for(auto& alien: aliens) {
        alien.position.y += distance;
    }
}

void Game::aliens_shoot() {
    // Get time and if current time is greq to interval and aliens are on screen fire
    double curr_time = GetTime();
    if(curr_time - last_al_laser_time >= al_shot_intv && !aliens.empty()) {

        // Pick a random alien and have it fire a laser
        int rand_idx = GetRandomValue(0, aliens.size() - 1);
        Alien& alien = aliens[rand_idx];
        al_laser.push_back(Laser({alien.position.x + alien.alien_images[alien.type - 1].width / 2,
        alien.position.y + alien.alien_images[alien.type - 1].height}, 6));
        // Update last fire time given completion of previous code
        last_al_laser_time = GetTime();
    }
}