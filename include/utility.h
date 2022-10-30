#ifndef RAYTRACER_UTILITY_H
#define RAYTRACER_UTILITY_H

#include <cstdlib>

#define PI 3.14159265359

// Return a random number in the interval [0,1)
double rand_number() {
    return std::rand() / (RAND_MAX + 1.0);
}

// Return a random number in the interval [min,max)
double random_double(double min, double max) {
    return min + (max - min) * rand_number();
}

// Clamp a value given the minimum and maximum threshold.
double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}


#endif
