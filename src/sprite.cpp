#include "sprite.h"
#include <stdexcept>  // For runtime_error

// Constructor: copies raw_data into the internal vector
Sprite::Sprite(size_t width, size_t height, const uint8_t* raw_data)
    : width(width), height(height), data(raw_data, raw_data + width * height) {}

// Destructor: nothing to manually delete — vector handles memory
Sprite::~Sprite() = default;

size_t Sprite::get_width() const {
    return width;
}

size_t Sprite::get_height() const {
    return height;
}

const uint8_t* Sprite::get_data() const {
    return data.data();
}

// Draws this sprite to the given buffer at position (x, y) using the given color
void Sprite::draw_to(Buffer& buffer, size_t x, size_t y, uint32_t color) const {
    for (size_t row = 0; row < height; ++row) {
        for (size_t col = 0; col < width; ++col) {
            if (data[row * width + col]) {
                size_t px = x + col;
                size_t py = y + row;
                if (px < buffer.width && py < buffer.height) {
                    buffer.data[py * buffer.width + px] = color;
                }
            }
        }
    }
}

// Check if two sprites overlap given their top-left positions
bool sprite_over_lap(const Sprite& sp_a, size_t x_a, size_t y_a,
                    const Sprite& sp_b, size_t x_b, size_t y_b) {
    return x_a < x_b + sp_b.get_width() &&
            x_a + sp_a.get_width() > x_b &&
            y_a < y_b + sp_b.get_height() &&
            y_a + sp_a.get_height() > y_b;
}

// Static alien sprite pixel data
static const uint8_t ALIEN_PIXELS[88] = {
    0,0,1,0,0,0,0,0,1,0,0,
    0,0,0,1,0,0,0,1,0,0,0,
    0,0,1,1,1,1,1,1,1,0,0,
    0,1,1,0,1,1,1,0,1,1,0,
    1,1,1,1,1,1,1,1,1,1,1,
    1,0,1,1,1,1,1,1,1,0,1,
    1,0,1,0,0,0,0,0,1,0,1,
    0,0,0,1,1,0,1,1,0,0,0
};

// Alien constructor using static memory
Alien::Alien() : Sprite(11, 8, ALIEN_PIXELS) {}


// Static player sprite pixel data
static const uint8_t PLAYER_PIXELS[77] = {
    0,0,0,0,0,1,0,0,0,0,0,
    0,0,0,0,1,1,1,0,0,0,0,
    0,0,0,0,1,1,1,0,0,0,0,
    0,1,1,1,1,1,1,1,1,1,0,
    1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1
};

// Player constructor using static memory
Player::Player() : Sprite(11, 7, PLAYER_PIXELS) {}