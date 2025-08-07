#include "Platformer/Random.hpp"
#include <cstdlib>

float Platformer::Random::random(const float max) {
    return randomRange(0.f, max);
}

float Platformer::Random::randomRange(const float min, const float max) {
    return randomNormal() * (max - min) + min;
}

float Platformer::Random::randomNormal() {
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}
