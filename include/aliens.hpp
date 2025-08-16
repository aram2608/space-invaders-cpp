#pragma once
#include <raylib.h>

class Alien {
public:
    Alien(int type, Vector2 position);
    void draw();
    void update();
    int get_type();
    Texture2D image;
    int type;
    Vector2 position;
private:
};