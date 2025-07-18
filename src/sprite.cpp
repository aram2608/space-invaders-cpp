#include "sprite.h"
#include <cstring> // for memcpy
#include <stdexcept>


Sprite::Sprite(size_t width, size_t height, const uint8_t* raw_data)
    : width(width), height(height)
{
    size_t size = width * height;
    data = new uint8_t[size];
    std::memcpy(data, raw_data, size);
}

Sprite::~Sprite() {
    delete[] data;
}

size_t Sprite::get_width() const { return width; }
size_t Sprite::get_height() const { return height; }
const uint8_t* Sprite::get_data() const { return data; }

void Sprite::draw_to(Buffer& buffer, size_t x, size_t y, uint32_t color) const {
    for (size_t row = 0; row < height; ++row) {
        for (size_t col = 0; col < width; ++col) {
            if (data[row * width + col])
                buffer.data[(y + row) * buffer.width + (x + col)] = color;
        }
    }
}


Alien::Alien()
    : Sprite(11, 8, new uint8_t[88] {
        0,0,1,0,0,0,0,0,1,0,0,
        0,0,0,1,0,0,0,1,0,0,0,
        0,0,1,1,1,1,1,1,1,0,0,
        0,1,1,0,1,1,1,0,1,1,0,
        1,1,1,1,1,1,1,1,1,1,1,
        1,0,1,1,1,1,1,1,1,0,1,
        1,0,1,0,0,0,0,0,1,0,1,
        0,0,0,1,1,0,1,1,0,0,0
    }) {}


Player::Player()
    : Sprite(11, 7, new uint8_t[77] {
        0,0,0,0,0,1,0,0,0,0,0,
        0,0,0,0,1,1,1,0,0,0,0,
        0,0,0,0,1,1,1,0,0,0,0,
        0,1,1,1,1,1,1,1,1,1,0,
        1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1
    }) {}
