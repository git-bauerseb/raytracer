#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

#include <vector>

#include "r_object.h"

class Sphere : public RObject {
    public:

        Sphere(Vector3<float> center, float radius)
            : m_center(center), m_radius(radius) {}

        bool hit(const Ray& ray, HitInfo& hit) const override;

    private:
        Vector3<float> m_center;
        float m_radius;

};

#endif