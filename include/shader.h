// shader.h
#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>

class Shader {
public:
    Shader(const char* vertex_src, const char* fragment_src);
    ~Shader();

    void use() const;
    GLuint id() const;

private:
    GLuint program_id;

    bool validate_shader(GLuint shader, const char* label);
    bool validate_program(GLuint program);
};

#endif  // SHADER_H