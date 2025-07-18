// main.cpp
#include <iostream>
#include <cstddef>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <buffer.h>
#include <texture.h>
#include <shader.h>
#include <sprite.h>
#include <window.h>

const char* vertex_src = R"(
#version 330
noperspective out vec2 TexCoord;
void main() {
    TexCoord.x = (gl_VertexID == 2) ? 2.0 : 0.0;
    TexCoord.y = (gl_VertexID == 1) ? 2.0 : 0.0;
    gl_Position = vec4(2.0 * TexCoord - 1.0, 0.0, 1.0);
}
)";

const char* fragment_src = R"(
#version 330
uniform sampler2D buffer;
noperspective in vec2 TexCoord;
out vec3 outColor;
void main() {
    outColor = texture(buffer, TexCoord).rgb;
}
)";

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

class Game {
public:
    Game(size_t width, size_t height);

    void update();
    void render(Buffer& buffer);

private:
    size_t width, height;
    size_t num_aliens;
    Alien* aliens;
    Player player;
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

        // Create our graphics buffer
        Buffer buffer(224, 256);
        buffer.clear(rgb_to_uint32(0, 128, 0));

        // Texture
        Texture texture(buffer.width, buffer.height, buffer.data);
        GLuint vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        // Shader
        Shader shader(vertex_src, fragment_src);
        shader.use();
        glUniform1i(glGetUniformLocation(shader.id(), "buffer"), 0);
        glDisable(GL_DEPTH_TEST);
        glActiveTexture(GL_TEXTURE0);

        // Sprites
        Alien alien;
        Player player;

        uint32_t clear_color = rgb_to_uint32(0, 128, 0);
        uint32_t alien_color = rgb_to_uint32(128, 0, 0);
        uint32_t player_color = rgb_to_uint32(0,0,250);

        // Game loop
        while (!glfwWindowShouldClose(window.get())) {
            buffer.clear(clear_color);
            alien.draw_to(buffer, 112, 128, alien_color);
            player.draw_to(buffer, 100, 240, player_color);

            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, buffer.width, buffer.height,
                            GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, buffer.data);

            glClear(GL_COLOR_BUFFER_BIT);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

            // GL has two buffers, a front and back. The game loop swaps between these two constantly
            glfwSwapBuffers(window.get());
            glfwPollEvents();
        }

        glDeleteVertexArrays(1, &vao);

        // Catch errors and close program
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwTerminate();
    return 0;
}