#ifndef RAYTRACER_UTILITY_H
#define RAYTRACER_UTILITY_H

#include <random>
#include <memory>

inline double rand_number() {
    return rand() / (RAND_MAX + 1.0);
}

inline double rand_number(double min, double max) {
    return min + (max - min) * rand_number();
}

inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

#endif