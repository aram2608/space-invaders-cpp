// sprite.h
#ifndef SPRITE_H
#define SPRITE_H

#include <cstddef>
#include <cstdint>
#include "buffer.h"

class Sprite {
public:
    Sprite(size_t width, size_t height, const uint8_t* raw_data);
    ~Sprite();

    size_t get_width() const;
    size_t get_height() const;
    const uint8_t* get_data() const;

    void draw_to(Buffer& buffer, size_t x, size_t y, uint32_t color) const;

private:
    size_t width, height;
    uint8_t* data;
};

#endif