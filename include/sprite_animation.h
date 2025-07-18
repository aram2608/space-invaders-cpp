// sprite_animation.h
#ifndef SPRITE_ANIMATION_H
#define SPRITE_ANIMATION_H

#include <vector>
#include "sprite.h"

class SpriteAnimation {
public:
    SpriteAnimation(bool loop, size_t frame_duration, std::vector<const Sprite*> frames);
    const Sprite& current() const;
    void update();

private:
    bool loop;
    size_t duration;
    size_t time;
    std::vector<const Sprite*> frames;
};

#endif  // SPRITE_ANIMATION_H