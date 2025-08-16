#pragma once
#include <raylib.h>

class Alien {
public:
    Alien(int type, Vector2 position);
    void draw();
    void update();
    int get_type();
    static Texture2D alien_images[3];
    int type;
    Vector2 position;
private:
};