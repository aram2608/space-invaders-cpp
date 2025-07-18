#include "sprite.h"
#include <cstring>

Sprite::Sprite(size_t width, size_t height, const uint8_t* raw_data)
    : width(width), height(height), data(new uint8_t[width * height]) {
    std::memcpy(data, raw_data, width * height);
}

Sprite::~Sprite() {
    delete[] data;
}

size_t Sprite::get_width() const { return width; }
size_t Sprite::get_height() const { return height; }
const uint8_t* Sprite::get_data() const { return data; }

void Sprite::draw_to(Buffer& buffer, size_t x, size_t y, uint32_t color) const {
    for(size_t xi = 0; xi < width; ++xi) {
        for(size_t yi = 0; yi < height; ++yi) {
            if(data[yi * width + xi] &&
                (height - 1 + y - yi) < buffer.height &&
                (x + xi) < buffer.width)
            {
                buffer.data[(height - 1 + y - yi) * buffer.width + (x + xi)] = color;
            }
        }
    }
}
