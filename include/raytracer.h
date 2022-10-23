#ifndef RAYTRACER_RAYTRACER_H
#define RAYTRACER_RAYTRACER_H

class Material;

// Abstract object representing an render object that can interact
// with the raytracer.
struct HitInfo {
    Vector3<double> m_position;     // Position in world space where
    // object was hti
    Vector3<double> m_normal;       // Normal of the object at the hit
    // position
    double m_t;                     // The value t for which
    // a + t * b is the hit position along
    // the ray

    std::shared_ptr<Material> m_material;
};

#endif