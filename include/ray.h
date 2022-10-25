#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include "vec3.h"

class Ray {

    public:
        Ray(const vec3 origin, const vec3 direction)
            : m_origin(origin), m_direction(direction) {}
        Ray() {}

        vec3 direction() const {return m_direction;}
        vec3 origin() const {return m_origin;}

        vec3 at(double scalar) const;

    private:
        vec3 m_origin;
        vec3 m_direction;
};

#endif