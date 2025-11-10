#pragma once
#include <raylib.h>

class Laser {
  public:
    // Constructor - Laser - Takes Vector and int
    Laser(Vector2 position, int speed);
    // Function to update laser position
    void update(float &delta);
    // Function to draw lasers to screen, handled with raylib
    void draw();
    // Function to get rectangle for lasers
    Rectangle get_rect();

    bool active_;

  private:
    Vector2 position_;
    float speed_;
};