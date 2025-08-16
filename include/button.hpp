#pragma once
#include <raylib.h>

class Button{
    public:
        // Constructor Button- Takes const char* Vector2 and float
        Button(const char* imagePath, Vector2 imagePosition, float scale);
        ~Button();
        // Function to draw to screen
        void draw();
        // Function to detect if button is pressed
        bool is_pressed(Vector2 mousePos, bool mousePressed);
    private:
        Texture2D texture;
        Vector2 position;
};