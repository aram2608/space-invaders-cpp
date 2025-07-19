#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "window.h"
#include "shader.h"
#include "buffer.h"
#include "texture.h"
#include "game.h"

// Vertex + fragment shaders
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
    outColor = texture(buffer, vec2(TexCoord.x, 1.0 - TexCoord.y)).rgb;
}
)";

// Error handlers
void error_callback(int error, const char* description) {
    std::cerr << "GLFW Error [" << error << "]: " << description << '\n';
}

inline void gl_debug(const char* file, int line) {
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL Error: " << err << " at " << file << ":" << line << "\n";
    }
}

int main() {
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW.\n";
        return -1;
    }

    try {
        Window window(640, 480, "Space Invaders");

        if (glewInit() != GLEW_OK) {
            std::cerr << "GLEW initialization failed.\n";
            return -1;
        }

        gl_debug(__FILE__, __LINE__);

        std::cout << "GL: " << glGetString(GL_VERSION) << "\n";
        std::cout << "Renderer: " << glGetString(GL_RENDERER) << "\n";
        std::cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";

        glClearColor(0.2f, 0.0f, 0.3f, 1.0f);

        // Set up render state
        GLuint vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        Shader shader(vertex_src, fragment_src);
        shader.use();
        glUniform1i(glGetUniformLocation(shader.id(), "buffer"), 0);
        glDisable(GL_DEPTH_TEST);
        glActiveTexture(GL_TEXTURE0);

        // Game setup
        Game game(224, 256);  // Width and height of your logical resolution

        // Player input
        game.handle_input(window.get());

        // Main loop
        while (!glfwWindowShouldClose(window.get())) {
            game.update();
            game.render();

            glClear(GL_COLOR_BUFFER_BIT);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
            glfwSwapBuffers(window.get());
            glfwPollEvents();
        }

        glDeleteVertexArrays(1, &vao);
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << "\n";
        glfwTerminate();
        return -1;
    }

    glfwTerminate();
    return 0;
}
