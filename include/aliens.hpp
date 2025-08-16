#pragma once
#include <raylib.h>

class Alien {
public:
    // Constructor
    Alien(int type, Vector2 position);
    // Class methods - Alien
    void draw();
    void update(int direction);
    int get_type();
    int type;
    Vector2 position;

    // Static methods - Alien
    static void unload_images();
    static Texture2D alien_images[3];
private:
};