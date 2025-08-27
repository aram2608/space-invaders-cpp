#pragma once
#include <raylib.h>

class Alien {
  public:
    // Constructor - Alien - Takes int and Vector2
    Alien(int type, Vector2 position);

    // Function to draw aliens to screen given a position in the vector
    void draw();
    // Function to update direction variable
    void update(int direction);
    // Function to retrive alien type
    int get_type();
    // Function to unload textures after game ends, prevents mem leaks
    static void unload_images();
    // Function to get rectangle for aliens
    Rectangle get_rect();

    int     type;
    Vector2 position;
    // Store alien images into an array, improves loading time
    static Texture2D alien_images[3];

  private:
};