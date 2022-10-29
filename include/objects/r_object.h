#ifndef RAYTRACER_ROBJECT_H
#define RAYTRACER_ROBJECT_H

#include <memory>
#include <limits>
#include "vec3.h"
#include "ray.h"
#include "material.h"
#include "raytracer.h"

class RObject {
    public:
    virtual bool hit(
            const Ray& r,
            double t_min,
            double t_max,
            HitInfo& rec
    ) const =0;
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

        void add(std::shared_ptr<RObject>& object) {
            m_objects.push_back(object);
        }

        virtual bool hit(
            const Ray& r, double t_min, double t_max, HitInfo& rec) const override {
            HitInfo tmp_hit;
            bool has_hit = false;
            double closest = std::numeric_limits<double>::max();

            for (const auto& obj : m_objects) {
                if (obj->hit(r, 0, closest, tmp_hit)) {
                    has_hit = true;
                    closest = tmp_hit.m_t;
                    rec = tmp_hit;
                }
            }

            return has_hit;
        }

    private:
        std::vector<std::shared_ptr<RObject>> m_objects;
};

#endif