#include "game.hpp"
#include <iostream>

Game::Game() {
    obstacles = make_obs();
    aliens = make_alien();
}

Game::~Game() {
}

void Game::update() {
    // Iterate over vector of lasers and update positions
    for(auto& laser: ship.lasers) {
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