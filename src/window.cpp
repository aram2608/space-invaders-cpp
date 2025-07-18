// window.cpp
#include "window.h"

// Constructor: sets up a window using GLFW with OpenGL context
Window::Window(int width, int height, const char* title) {
    // Request an OpenGL 3.3 Core Profile context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);      // Major version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);      // Minor version
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Core Profile = modern OpenGL
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // For Mac compatibility

    // Attempt to create the GLFW window
    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window) {
        // If creation fails, throw a C++ exception
        throw std::runtime_error("Failed to create GLFW window");
    }

    // Make this window's context the current one for OpenGL commands
    glfwMakeContextCurrent(window);
}

// Destructor: properly destroys the GLFW window
Window::~Window() {
    if (window) {
        glfwDestroyWindow(window);
    }
}

// Getter function for accessing the raw GLFWwindow* pointer
GLFWwindow* Window::get() const {
    return window;
}
