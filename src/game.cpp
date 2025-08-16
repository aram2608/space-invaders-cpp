#include "game.hpp"
#include <iostream>

Game::Game() {

}

Game::~Game() {

}

void Game::update() {
    for(auto& laser: ship.lasers) {
        laser.update();
    }

    delete_laser();
}

void Game::draw() {
    ship.draw();

    for(auto& laser: ship.lasers) {
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