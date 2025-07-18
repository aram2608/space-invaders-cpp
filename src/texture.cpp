#include "texture.h"

Texture::Texture(size_t width, size_t height, const uint32_t* data)
    : width(width), height(height) {

    glGenTextures(1, &tex_id);
    glBindTexture(GL_TEXTURE_2D, tex_id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0,
                GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void Texture::upload(const uint32_t* data) {
    glBindTexture(GL_TEXTURE_2D, tex_id);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height,
                    GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, data);
}

Texture::~Texture() {
    glDeleteTextures(1, &tex_id);
}
