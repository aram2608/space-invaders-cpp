// buffer.cpp
#include "buffer.h"
#include <algorithm> // for std::fill

// Constructor: Allocate memory for pixel buffer using new[]
// Use RAII to ensure this memory is safely managed in the destructor
Buffer::Buffer(size_t width, size_t height)
    : width(width), height(height), data(new uint32_t[width * height]) {}

// Destructor: Deallocate pixel buffer to avoid memory leaks
Buffer::~Buffer() {
    delete[] data; // Always pair new[] with delete[]
}

// Clear the buffer by filling it with a single color
void Buffer::clear(uint32_t color) {
    std::fill(data, data + width * height, color); // Efficient fill
}

// Convert RGB values (0-255) to a packed 32-bit integer in RGBA format
// The final 8 bits are alpha = 255 (opaque)
uint32_t rgb_to_uint32(uint8_t r, uint8_t g, uint8_t b) {
    return (r << 24) | (g << 16) | (b << 8) | 255;
}