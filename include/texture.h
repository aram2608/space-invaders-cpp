// texture.h
#ifndef TEXTURE_H
#define TEXTURE_H

#include <cstdint>
#include <cstddef>
#include <GL/glew.h>
#include "buffer.h"

class Texture {
public:
    Texture(size_t width, size_t height, const uint32_t* data);
    ~Texture();

    void update(const Buffer& buffer);
    void upload(const uint32_t* data);
    GLuint id() const { return tex_id; }

private:
    GLuint tex_id;
    size_t width, height;
};

#endif  // TEXTURE_H