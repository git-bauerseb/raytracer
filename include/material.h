#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H

#include "ray.h"
#include "vec3.h"
#include "raytracer.h"

class Material {
    public:
        virtual bool scatter(const Ray& ray,
                             const HitInfo& hit,
                             vec3& attenuation,
                             Ray& scattered) const =0;
};

class Lambertian : public Material {
    public:
        Lambertian(const vec3& a) : m_albedo(a) {}

        virtual bool scatter(const Ray &ray, const HitInfo &hit, vec3 &attenuation, Ray &scattered) const override {
            vec3 scatter_dir = hit.m_normal + random_unit_vector();

            if (scatter_dir.near_zero()) {
                scatter_dir = hit.m_normal;
            }

            scattered = Ray(hit.m_position, scatter_dir);
            attenuation = m_albedo;
            return true;
        }

    private:
        vec3 m_albedo;
};

class Metal : public Material {
    public:
        Metal(const vec3& a, double fuzz) : m_albedo(a), m_fuzz_factor(fuzz < 1 ? fuzz : 1) {}

        virtual bool scatter(const Ray &ray, const HitInfo &hit, vec3 &attenuation, Ray &scattered) const override {
            vec3 reflected = reflect(unit_vector(ray.direction()), hit.m_normal)
                    + m_fuzz_factor * random_in_unit_sphere();
            scattered = Ray(hit.m_position, reflected + m_fuzz_factor * random_in_unit_sphere());
            attenuation = m_albedo;
            return dot(scattered.direction(),hit.m_normal) > 0;
        }

    private:
        vec3 m_albedo;
        double m_fuzz_factor;
};

class Dielectric : public Material {
    public:
        Dielectric(double coeff) : m_coefficient(coeff) {}

        virtual bool scatter(const Ray& r_in, const HitInfo& rec, vec3& attenuation, Ray& scattered) const override {
            attenuation = color(1.0, 1.0, 1.0);
            double refraction_ratio = rec.front_face ? (1.0/m_coefficient) : m_coefficient;

            vec3 unit_direction = unit_vector(r_in.direction());
            double cos_theta = fmin(dot(-unit_direction, rec.m_normal), 1.0);
            double sin_theta = sqrt(1.0 - cos_theta*cos_theta);

            bool cannot_refract = refraction_ratio * sin_theta > 1.0;
            vec3 direction;

            if (cannot_refract || reflectance(cos_theta, refraction_ratio) > rand_number())
                direction = reflect(unit_direction, rec.m_normal);
            else
                direction = refract(unit_direction, rec.m_normal, refraction_ratio);

            scattered = Ray(rec.m_position, direction);
            return true;
        }

    private:
        double m_coefficient;

        static double reflectance(double cosine, double ref_idx) {
            auto r0 = (1 - ref_idx) / (1 + ref_idx);
            r0 = r0 * r0;
            return r0 + (1 - r0) * std::pow((1 - cosine), 5);
        }
};

#endif