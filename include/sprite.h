#ifndef SPRITE_H
#define SPRITE_H

#include <cstddef>
#include <cstdint>
#include <vector>
#include "buffer.h"

// A generic pixel-based sprite.
// Stores width x height binary pixel data (1 = draw, 0 = transparent).
class Sprite {
public:
    // Construct from raw binary data (assumed row-major layout)
    Sprite(size_t width, size_t height, const uint8_t* raw_data);

    // Virtual destructor for inheritance safety
    virtual ~Sprite();

    // Accessors
    size_t get_width() const;
    size_t get_height() const;
    const uint8_t* get_data() const;

    // Draws the sprite to the given buffer at (x, y) using a specific color
    virtual void draw_to(Buffer& buffer, size_t x, size_t y, uint32_t color) const;

protected:
    size_t width, height;
    std::vector<uint8_t> data;
};

// Represents a classic alien sprite
class Alien : public Sprite {
public:
    Alien();
    ~Alien() override = default;
};

// Represents the player sprite
class Player : public Sprite {
public:
    Player();
    ~Player() override = default;
};

// Returns true if two sprites overlap on screen
bool sprite_over_lap(const Sprite& sp_a, size_t x_a, size_t y_a,
                    const Sprite& sp_b, size_t x_b, size_t y_b);

#endif  // SPRITE_H
