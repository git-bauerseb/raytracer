#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include "math/vector3.h"

class Ray {
    public:
        Ray() {}
        Ray(const Vector3& origin, const Vector3& direction)
                : orig(origin), dir(direction) {}

        Vector3 origin() const {
            return orig;
        }

        Vector3 direction() const {
            return dir;
        }

        Vector3 at(double t) const {
            return orig + t * dir;
        }

    private:
        Vector3 orig;
        Vector3 dir;
};

#endif
