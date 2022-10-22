#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include "vec3.h"

class Ray {

    public:
        Ray(Vector3<float> origin, Vector3<float> direction)
            : m_origin(origin), m_direction(direction) {}
        Ray() {}

        Vector3<float> direction() const {return m_direction;}
        Vector3<float> origin() const {return m_origin;}

    private:
        Vector3<float> m_origin;
        Vector3<float> m_direction;
};

#endif