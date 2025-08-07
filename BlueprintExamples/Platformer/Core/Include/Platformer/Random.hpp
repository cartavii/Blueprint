#ifndef PLATFORMER_CORE_RANDOM_HPP
#define PLATFORMER_CORE_RANDOM_HPP

namespace Platformer {
class Random {
public:
    static float random(float max);
    static float randomRange(float min, float max);
    static float randomNormal();
};
} // Platformer

#endif // PLATFORMER_CORE_RANDOM_HPP
