// sprite.h
#ifndef SPRITE_H
#define SPRITE_H

#include <cstddef>
#include <cstdint>
#include "buffer.h"

class Sprite {
public:
    Sprite(size_t width, size_t height, const uint8_t* raw_data);
    virtual ~Sprite();

    size_t get_width() const;
    size_t get_height() const;
    const uint8_t* get_data() const;

    virtual void draw_to(Buffer& buffer, size_t x, size_t y, uint32_t color) const;

protected:
    size_t width, height;
    uint8_t* data;
};

class Alien : public Sprite {
public:
    Alien();
    ~Alien() override = default;
};

class Player : public Sprite {
public:
    Player();
    ~Player() override = default;
};

#endif