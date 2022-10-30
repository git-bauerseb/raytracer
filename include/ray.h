#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include "math/vector3.h"

class Ray {
    public:
        Ray() {}
        Ray(const point3& origin, const Vector3& direction)
                : orig(origin), dir(direction) {}

        point3 origin() const {
            return orig;
        }

        Vector3 direction() const {
            return dir;
        }

        point3 at(double t) const {
            return orig + t * dir;
        }

    private:
        point3 orig;
        Vector3 dir;
};

#endif
