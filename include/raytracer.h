#ifndef RAYTRACER_RAYTRACER_H
#define RAYTRACER_RAYTRACER_H

#include <mutex>
#include <thread>
#include <memory>

#include "objects/render_object.h"
#include "math/vector3.h"

class Material;

struct HitRecord {
    point3 p;
    Vector3 normal;
    double t;
    bool front_face;
    std::shared_ptr<Material> mat_ptr;

    inline void set_face_normal(const Ray& r, const Vector3& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

#endif
