#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

#include <vector>

#include "r_object.h"

class Sphere : public RObject {
    public:

        Sphere(Vector3<double> center, double radius)
            : m_center(center), m_radius(radius) {}

        bool hit(const Ray& ray, HitInfo& hit, double t_min, double t_max) const override;

    private:
        Vector3<double> m_center;
        double m_radius;

};

#endif