// shader.cpp
#include "shader.h"
#include <iostream>

Shader::Shader(const char* vertex_src, const char* fragment_src) {
    GLuint shader_v = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shader_v, 1, &vertex_src, nullptr);
    glCompileShader(shader_v);
    validate_shader(shader_v, "vertex");

    GLuint shader_f = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shader_f, 1, &fragment_src, nullptr);
    glCompileShader(shader_f);
    validate_shader(shader_f, "fragment");

    program_id = glCreateProgram();
    glAttachShader(program_id, shader_v);
    glAttachShader(program_id, shader_f);
    glLinkProgram(program_id);

    validate_program(program_id);

    glDeleteShader(shader_v);
    glDeleteShader(shader_f);
}

Shader::~Shader() {
    glDeleteProgram(program_id);
}

void Shader::use() const {
    glUseProgram(program_id);
}

GLuint Shader::id() const {
    return program_id;
}

bool Shader::validate_shader(GLuint shader, const char* label) {
    char buffer[512];
    GLsizei length;
    glGetShaderInfoLog(shader, 512, &length, buffer);
    if (length > 0) {
        std::cerr << "Shader (" << label << ") error: " << buffer << std::endl;
        return false;
    }
    return true;
}

bool Shader::validate_program(GLuint program) {
    char buffer[512];
    GLsizei length;
    glGetProgramInfoLog(program, 512, &length, buffer);
    if (length > 0) {
        std::cerr << "Program link error: " << buffer << std::endl;
        return false;
    }
    return true;
}
