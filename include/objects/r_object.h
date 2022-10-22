#ifndef RAYTRACER_ROBJECT_H
#define RAYTRACER_ROBJECT_H

#include "vec3.h"
#include "ray.h"

// Abstract object representing an render object that can interact
// with the raytracer.
struct HitInfo {
    Vector3<float> m_position;      // Position in world space where
                                    // object was hti
    Vector3<float> m_normal;        // Normal of the object at the hit
                                    // position
    float m_t;                      // The value t for which
                                    // a + t * b is the hit position along
                                    // the ray
};

class RObject {
    public:
        virtual bool hit(const Ray& ray, HitInfo& hit) const =0;
};



#endif