// window.h
#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
#include <stdexcept>

class Window {
public:
    // Constructor
    Window(int width, int height, const char* title);

    // Deconstructor
    ~Window();

    GLFWwindow* get() const;

private:
    GLFWwindow* window;
};

#endif
