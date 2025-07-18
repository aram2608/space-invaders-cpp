// texture.cpp
#include "texture.h"

// Constructor: generates and configures an OpenGL texture from a raw pixel buffer
Texture::Texture(size_t width, size_t height, const uint32_t* data)
    : width(width), height(height) {

    // Generate a texture ID and bind it so subsequent operations affect it
    glGenTextures(1, &tex_id);
    glBindTexture(GL_TEXTURE_2D, tex_id);

    // Allocate texture storage and upload initial pixel data
    glTexImage2D(
        GL_TEXTURE_2D,      // Target
        0,                  // Mipmap level
        GL_RGB8,            // Internal format (store as 24-bit RGB)
        width, height,      // Dimensions
        0,                  // Border (must be 0)
        GL_RGBA,            // Input format
        GL_UNSIGNED_INT_8_8_8_8, // Input data type (matches uint32_t layout)
        data                // Pointer to pixel data
    );

    // Set nearest-neighbor filtering (pixelated look)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

// Update the entire texture from a Buffer object
void Texture::update(const Buffer& buffer) {
    glBindTexture(GL_TEXTURE_2D, tex_id);
    glTexSubImage2D(
        GL_TEXTURE_2D, 0, 0, 0,
        buffer.width, buffer.height,
        GL_RGBA, GL_UNSIGNED_INT_8_8_8_8,
        buffer.data
    );
}

// Upload new pixel data directly (same shape as original)
void Texture::upload(const uint32_t* data) {
    glBindTexture(GL_TEXTURE_2D, tex_id);
    glTexSubImage2D(
        GL_TEXTURE_2D, 0, 0, 0,
        width, height,
        GL_RGBA, GL_UNSIGNED_INT_8_8_8_8,
        data
    );
}

// Destructor: cleans up OpenGL texture
Texture::~Texture() {
    glDeleteTextures(1, &tex_id);
}
