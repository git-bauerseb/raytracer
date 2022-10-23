#ifndef RAYTRACER_ROBJECT_H
#define RAYTRACER_ROBJECT_H

#include <memory>
#include <limits>
#include "vec3.h"
#include "ray.h"

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
};

class RObject {
    public:
        virtual bool hit(const Ray& ray, HitInfo& hit, double t_min, double t_max) const =0;
};

class RObjectList : public RObject {

    public:
        RObjectList() =default;

        void clear() {
            m_objects.clear();
        }

        void add(std::shared_ptr<RObject> object) {
            m_objects.push_back(object);
        }

        bool hit(const Ray& ray, HitInfo& hit, double t_min, double t_max) const override {
            HitInfo tmp_hit;
            bool has_hit = false;
            double closest = std::numeric_limits<double>::max();

            for (const auto& obj : m_objects) {
                if (obj->hit(ray, tmp_hit, 0, closest)) {
                    has_hit = true;
                    closest = tmp_hit.m_t;
                    hit = tmp_hit;
                }
            }

            return has_hit;
        }

    private:
        std::vector<std::shared_ptr<RObject>> m_objects;
};

#endif