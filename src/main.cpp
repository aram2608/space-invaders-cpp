#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

const char* getGLErrorString(GLenum err) {
    switch (err) {
        case GL_INVALID_ENUM: return "GL_INVALID_ENUM";
        case GL_INVALID_VALUE: return "GL_INVALID_VALUE";
        case GL_INVALID_OPERATION: return "GL_INVALID_OPERATION";
        case GL_INVALID_FRAMEBUFFER_OPERATION: return "GL_INVALID_FRAMEBUFFER_OPERATION";
        case GL_OUT_OF_MEMORY: return "GL_OUT_OF_MEMORY";
        default: return "UNKNOWN_ERROR";
    }
}

inline void gl_debug(const char* file, int line) {
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << getGLErrorString(err) << " - " << file << ": " << line << std::endl;
    }
}

void error_callback(int error, const char* description) {
    std::cerr << "GLFW Error [" << error << "]: " << description << '\n';
}

class Window {
public:
    Window(int width, int height, const char* title) {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!window) throw std::runtime_error("Failed to create GLFW window");

        glfwMakeContextCurrent(window);
    }

    ~Window() {
        if (window) glfwDestroyWindow(window);
    }

    GLFWwindow* get() const { return window; }

private:
    GLFWwindow* window;
};

int main(int argc, char* argv[]) {

    // Sets our error callback
    glfwSetErrorCallback(error_callback);

    // Initializes GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW." << std::endl;
        return -1;
    }

    // Try RAII style window
    try {
        Window window(640, 480, "Space Invaders");

        // Initialize GLEW so we don't get a segfault
        GLenum err = glewInit();
        if (err != GLEW_OK) {
            std::cerr << "Error initializing GLEW: "
                    << glewGetErrorString(err) << std::endl;
            return -1;
        }

        // Query the versions
        int glVersion[2] = {-1, 1};
        glGetIntegerv(GL_MAJOR_VERSION, &glVersion[0]);
        glGetIntegerv(GL_MINOR_VERSION, &glVersion[1]);

        gl_debug(__FILE__, __LINE__);

        std::cout << "Using OpenGL: " << glVersion[0] << "." << glVersion[1] << std::endl;
        std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
        std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

        // Sets clear color, bright red
        glClearColor(1.0, 0.0, 0.0, 1.0);

        // Game loop
        while (!glfwWindowShouldClose(window.get())) {
            glClear(GL_COLOR_BUFFER_BIT);
            glfwSwapBuffers(window.get());
            glfwPollEvents();
        }
    // Catch errors
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwTerminate();
    return 0;
}