#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

#include <utility>
#include <vector>
#include "r_object.h"

class Sphere : public RObject {
    public:

        Sphere(vec3 center, double radius, std::shared_ptr<Material> material)
            : m_center(center), m_radius(radius), m_material(std::move(material)) {}

    virtual bool hit(
            const Ray& r,
            double t_min,
            double t_max,
            HitInfo& rec
    ) const override {
            vec3 oc = r.origin() - m_center;
            auto a = r.direction().length_squared();
            auto half_b = dot(oc, r.direction());
            auto c = oc.length_squared() - m_radius * m_radius;

            auto discriminant = half_b*half_b - a*c;
            if (discriminant < 0) return false;
            auto sqrtd = sqrt(discriminant);

            // Find the nearest root that lies in the acceptable range.
            auto root = (-half_b - sqrtd) / a;
            if (root < t_min || t_max < root) {
                root = (-half_b + sqrtd) / a;
                if (root < t_min || t_max < root)
                    return false;
            }

            rec.m_t = root;
            rec.m_position = r.at(rec.m_t);
            vec3 normal = (rec.m_position - m_center) / m_radius;
            rec.set_face_normal(r, normal);
            rec.m_material = m_material;

            return true;
        }

    private:
        vec3 m_center;
        double m_radius;
        std::shared_ptr<Material> m_material;

};

#endif