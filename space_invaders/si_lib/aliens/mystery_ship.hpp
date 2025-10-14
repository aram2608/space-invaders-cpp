#pragma once
#include <raylib.h>

class MysteryShip {
  public:
    // Constructor - MysteryShip
    MysteryShip();
    // Destructor - MysteryShip
    ~MysteryShip();
    // Function to update mystery ship position
    void update(float &delta);
    // Function to draw mystery ship to screen
    void draw();
    // Function to handle firing of ship laser
    void spawn();
    // Function to get rectangle for mystery ship
    Rectangle get_rect();

    bool alive;

  private:
    Texture2D image;
    Vector2 position;
    int speed;
    Sound myst_ship_sound;
};