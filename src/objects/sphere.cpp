#include "objects/sphere.h"

bool Sphere::hit(const Ray& r, HitInfo& rec, double t_min, double t_max) const {
    vec3 oc = r.origin() - m_center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - m_radius*m_radius;

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
    auto outward_normal = (rec.m_position - m_center) / m_radius;
    rec.set_face_normal(r, outward_normal);
    rec.m_material = m_material;

    return true;
}