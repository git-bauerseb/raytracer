#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

#include <utility>
#include <vector>
#include "r_object.h"

class Sphere : public RObject {
    public:

        Sphere(Vector3<double> center, double radius, std::shared_ptr<Material> material)
            : m_center(center), m_radius(radius), m_material(std::move(material)) {}

        bool hit(const Ray& ray, HitInfo& hit, double t_min, double t_max) const override;

    private:
        Vector3<double> m_center;
        double m_radius;
        std::shared_ptr<Material> m_material;

};

#endif