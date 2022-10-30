#ifndef RAYTRACER_OBJECTS_SPHERE_H
#define RAYTRACER_OBJECTS_SPHERE_H

#include "render_object.h"

class Sphere : public RenderObject {
public:
    Sphere() {}
    Sphere(Vector3 cen, double r, std::shared_ptr<Material> m)
            : center(cen), radius(r), mat_ptr(m) {}

    virtual bool hit(
            const Ray& r,
            double t_min,
            double t_max,
            HitRecord& rec
    ) const override;

private:
    Vector3 center;
    double radius;
    std::shared_ptr<Material> mat_ptr;
};

bool Sphere::hit(const Ray& r,
                 double t_min,
                 double t_max,
                 HitRecord& rec) const {

    Vector3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius*radius;

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

    rec.t = root;
    rec.p = r.at(rec.t);
    Vector3 normal = (rec.p - center) / radius;
    rec.set_face_normal(r, normal);
    rec.mat_ptr = mat_ptr;

    return true;

}

#endif
