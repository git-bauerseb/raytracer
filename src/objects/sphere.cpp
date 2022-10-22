#include "objects/sphere.h"

bool Sphere::hit(const Ray& ray, HitInfo& hit) const {
    Vector3<float> oc = ray.origin() - m_center;
    float a = ray.direction().dot(ray.direction());
    float half_b = oc.dot(ray.direction());
    float c = oc.dot(oc) - m_radius * m_radius;

    float discriminant = half_b * half_b - a * c;
    float sqrt_discr = std::sqrt(discriminant);

    if (discriminant < 0) {
        return false;
    }

    float root = (-half_b - sqrt_discr) / a;

    hit.m_t = root;
    hit.m_position = ray.at(root);
    hit.m_normal = 1.0f / m_radius * (hit.m_position - m_center);

    return true;
}