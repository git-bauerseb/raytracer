#ifndef RAYTRACER_UTILITY_H
#define RAYTRACER_UTILITY_H

#include <random>

inline float rand_number() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline float rand_number(float min, float max) {
    return min + (max - min) * rand_number();
}

#endif