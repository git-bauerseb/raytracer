#ifndef RAYTRACER_RAYTRACER_H
#define RAYTRACER_RAYTRACER_H

class Material;

// Abstract object representing an render object that can interact
// with the raytracer.
struct HitInfo {
    vec3 m_position;     // Position in world space where
    // object was hti
    vec3 m_normal;       // Normal of the object at the hit
    // position
    double m_t;                     // The value t for which
    // a + t * b is the hit position along
    // the ray

    std::shared_ptr<Material> m_material;
    bool front_face = false;

    inline void set_face_normal(const Ray& r, const vec3& outward) {
        front_face = dot(r.direction(),outward) < 0;
        m_normal = front_face ? outward : -outward;
    }
};

#endif