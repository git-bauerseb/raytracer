#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include "vec3.h"

class Ray {

    public:
        Ray(Vector3<double> origin, Vector3<double> direction)
            : m_origin(origin), m_direction(direction) {}
        Ray() {}

        Vector3<double> direction() const {return m_direction;}
        Vector3<double> origin() const {return m_origin;}

        Vector3<double> at(double scalar) const;

    private:
        Vector3<double> m_origin;
        Vector3<double> m_direction;
};

#endif