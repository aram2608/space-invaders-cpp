// buffer.h
#ifndef BUFFER_H
#define BUFFER_H
#include <cstddef>
#include <cstdint>

class Buffer {
public:
    /* 
    Constructor for buffer, ie just a chunk of memory really
    uint32_t is used to store 4 8 bit color values for each pixel

    uint8_t could also be used but indexing an unsigned 32 bit integer is easier
    apparently
    */
    Buffer(size_t width, size_t height);

    // Deconstructor
    ~Buffer();

    // Method to clear buffer
    void clear(uint32_t color);

    size_t width, height;
    uint32_t* data;
};

// Function to get color values
uint32_t rgb_to_uint32(uint8_t r, uint8_t g, uint8_t b);

#endif