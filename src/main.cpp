#include <iostream>
#include <cstddef>
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

void validate_shader(GLuint shader, const char* file = 0)
{
    static const unsigned int BUFFER_SIZE = 512;
    char buffer[BUFFER_SIZE];
    GLsizei length = 0;

    glGetShaderInfoLog(shader, BUFFER_SIZE, &length, buffer);

    if(length > 0)
    {
        printf("Shader %d(%s) compile error: %s\n",
            shader, (file ? file: ""), buffer);
    }
}

bool validate_program(GLuint program)
{
    static const GLsizei BUFFER_SIZE = 512;
    GLchar buffer[BUFFER_SIZE];
    GLsizei length = 0;

    glGetProgramInfoLog(program, BUFFER_SIZE, &length, buffer);

    if(length > 0)
    {
        printf("Program %d link error: %s\n", program, buffer);
        return false;
    }

    return true;
}

// Function to get color values
uint32_t rgb_to_uint32(uint8_t r, uint8_t g, uint8_t b) {
    // Red, green, and blue
    return (r << 24) | (g << 16) | (b << 8) | 255;
}

// Function to clear buffer
void buffer_clear(Buffer* buffer, uint32_t color) {
    for(size_t i = 0; i < buffer->width * buffer->height; ++i) {
        buffer->data[i] = color;
    }
}

class Buffer {
public:
    /* 
    Constructor for buffer, ie just a chunk of memory really
    uint32_t is used to store 4 8 bit color values for each pixel

    uint8_t could also be used but indexing an unsigned 32 bit integer is easier
    apparently
    */
    Buffer(size_t width, size_t height, uint32_t data) {
        uint32_t clear_color = rgb_to_uint32(0, 128, 0);
        buffer.width  = buffer_width;
        buffer.height = buffer_height;
        buffer.data   = new uint32_t[buffer.width * buffer.height];
        buffer_clear(&buffer, clear_color);
    }

    ~Buffer() {
        delete Buffer;
    }
};

class Window {
public:
    // Constructor
    Window(int width, int height, const char* title) {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!window) throw std::runtime_error("Failed to create GLFW window");

        glfwMakeContextCurrent(window);
    }

    // Deconstructor
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

        // Sets clear color for our buffer, used in glClear()
        glClearColor(1.0, 0.0, 0.0, 1.0);

        // Game loop
        while (!glfwWindowShouldClose(window.get())) {
            glClear(GL_COLOR_BUFFER_BIT);
            // GL has two buffers, a front and back. The game loop swaps between these two constantly
            glfwSwapBuffers(window.get());
            // We need to update any ongoing events
            glfwPollEvents();
        }
    // Catch errors and close program
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        glfwTerminate();
        return -1;
    }

    // Terminate our program cleanly, the class handles deconstruction for itself
    // So we need to manually call glfwTerminate()
    glfwTerminate();
    return 0;
}