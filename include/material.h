#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H

#ifndef MATERIAL_H
#define MATERIAL_H

#include "ray.h"
#include "math/vector3.h"
#include "raytracer.h"

class Material {
    public:
        virtual bool scatter(
                const Ray& r_in, const HitRecord& rec, color& attenuation, Ray& scattered
        ) const = 0;
};

class Lambertian : public Material {
    public:
        Lambertian(const color& a) : albedo(a) {}

        virtual bool scatter(
                const Ray& r_in, const HitRecord& rec, color& attenuation, Ray& scattered
        ) const override {

            auto scatter_dir = rec.normal + random_unit_vector();

            if (scatter_dir.near_zero()) {
                scatter_dir = rec.normal;
            }

            scattered = Ray(rec.p, scatter_dir);
            attenuation = albedo;
            return true;

        }

    private:
        color albedo;
};

class Metal : public Material {
    public:
        Metal(const color& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

        virtual bool scatter(
                const Ray& r_in, const HitRecord& rec, color& attenuation, Ray& scattered
        ) const override {
            Vector3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
            scattered = Ray(rec.p, reflected + fuzz * random_in_unit_sphere());
            attenuation = albedo;
            return (dot(scattered.direction(), rec.normal) > 0);
        }

    private:
        color albedo;
        double fuzz;
};

class Dielectric : public Material {
    public:

        Dielectric(double index_of_refraction) : ir(index_of_refraction), m_albedo{1,1,1} {}

        Dielectric(double index_of_refraction, color albedo)
                : ir(index_of_refraction), m_albedo(albedo) {}

        virtual bool scatter(
                const Ray& r_in, const HitRecord& rec, color& attenuation, Ray& scattered
        ) const override {
            attenuation = m_albedo;
            double refraction_ratio = rec.front_face ? (1.0/ir) : ir;

            Vector3 unit_direction = unit_vector(r_in.direction());
            double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
            double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

            bool cannot_refract = refraction_ratio * sin_theta > 1.0;
            Vector3 dir;

            if (cannot_refract || reflectance(cos_theta, refraction_ratio) > rand_number()) {
                dir = reflect(unit_direction, rec.normal);
            } else {
                dir = refract(unit_direction, rec.normal, refraction_ratio);
            }


            scattered = Ray(rec.p, dir);
            return true;
        }

    private:
        double ir; // Index of Refraction
        color m_albedo;


        static double reflectance(double cosine, double ref_idx) {
            auto r0 = (1 - ref_idx) / (1 + ref_idx);
            r0 = r0 * r0;
            return r0 + (1 - r0) * pow((1 - cosine), 5);
        }
};

#endif

#endif