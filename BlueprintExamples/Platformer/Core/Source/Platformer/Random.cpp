#include "Platformer/Random.hpp"
#include <random>

float Platformer::Random::random(const float max) {
    return randomRange(0.f, max);
}

float Platformer::Random::randomRange(const float min, const float max) {
    return randomNormal() * (max - min) + min;
}

float Platformer::Random::randomNormal() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<float> dis(0.0f, 1.0f);
    return dis(gen);
}
