#pragma once
#include "ship/lasers.hpp"

#include <raylib.h>
#include <vector>

class SpaceShip {
  public:
    // Constructor - SpaceShip
    SpaceShip();
    // Function to draw ship to game window
    void draw();
    // Function to change x_coord left
    void move_left(float delta);
    // Function to change x_coord right
    void move_right(float delta);
    // Function to change y_coord up
    void move_up(float delta);
    // Function to change y_coord down
    void move_down(float delta);
    // Function to handle firing of ship laser
    void fire_laser();
    // Function to get rectangle for ship
    Rectangle get_rect();
    // Function to reset spaceship
    void reset();

    std::vector<Laser> lasers;

    // Deconstructor - SpaceShip
    ~SpaceShip();

  private:
    float speed;
    Texture2D image;
    Vector2 position;
    double fire_time;
    Sound laser_sound;
};