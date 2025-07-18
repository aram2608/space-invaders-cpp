// buffer.h
#ifndef BUFFER_H
#define BUFFER_H

#include <cstddef>
#include <cstdint>

class Buffer {
public:
    Buffer(size_t width, size_t height);
    ~Buffer();

    void clear(uint32_t color);

    size_t width, height;
    uint32_t* data;
};

uint32_t rgb_to_uint32(uint8_t r, uint8_t g, uint8_t b);

#endif  // BUFFER_H