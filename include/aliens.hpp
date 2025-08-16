#pragma once
#include <raylib.h>

class Alien {
public:
    Alien(int type, Vector2 position);
    void draw();
    void update(int direction);
    int get_type();
    int type;
    Vector2 position;

    static void unload_images();
    static Texture2D alien_images[3];
private:
};