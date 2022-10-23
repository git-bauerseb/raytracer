#include "objects/sphere.h"

bool Sphere::hit(const Ray& ray, HitInfo& hit, double t_min, double t_max) const {
    Vector3<double> oc = ray.origin() - m_center;
    double a = ray.direction().dot(ray.direction());
    double half_b = oc.dot(ray.direction());
    double c = oc.dot(oc) - m_radius * m_radius;

    double discriminant = half_b * half_b - a * c;
    double sqrt_discr = std::sqrt(discriminant);

    if (discriminant < 0) {
        return false;
    }

    double root = (-half_b - sqrt_discr) / a;

    if (root < t_min || t_max < root) {
        root = (-half_b + sqrt_discr) / a;
        if (root < t_min || t_max < root) {
            return false;
        }
    }

    hit.m_t = root;
    hit.m_position = ray.at(root);
    hit.m_normal = 1.0f / m_radius * (hit.m_position - m_center);
    hit.m_material = this->m_material;

    return true;
}