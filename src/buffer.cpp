#include "buffer.h"
#include <algorithm>

Buffer::Buffer(size_t width, size_t height)
    : width(width), height(height), data(new uint32_t[width * height]) {}

Buffer::~Buffer() {
    delete[] data;
}

void Buffer::clear(uint32_t color) {
    std::fill(data, data + width * height, color);
}

uint32_t rgb_to_uint32(uint8_t r, uint8_t g, uint8_t b) {
    return (r << 24) | (g << 16) | (b << 8) | 255;
}