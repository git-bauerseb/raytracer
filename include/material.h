#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H

#include "ray.h"
#include "vec3.h"
#include "raytracer.h"

class Material {
public:
    virtual bool scatter(
            const Ray& r_in, const HitInfo& rec, color& attenuation, Ray& scattered
    ) const = 0;
};

class Lambertian : public Material {
public:
    Lambertian(const color& a) : albedo(a) {}

    virtual bool scatter(
            const Ray& r_in, const HitInfo& rec, color& attenuation, Ray& scattered
    ) const override {

        auto scatter_dir = rec.m_normal + random_unit_vector();

        if (scatter_dir.near_zero()) {
            scatter_dir = rec.m_normal;
        }

        scattered = Ray(rec.m_position, scatter_dir);
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
            const Ray& r_in, const HitInfo& rec, color& attenuation, Ray& scattered
    ) const override {
        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.m_normal);
        scattered = Ray(rec.m_position, reflected + fuzz * random_in_unit_sphere());
        attenuation = albedo;
        return (dot(scattered.direction(), rec.m_normal) > 0);
    }

private:
    color albedo;
    double fuzz;
};

class Dielectric : public Material {
public:
    Dielectric(double index_of_refraction) : ir(index_of_refraction) {}

    virtual bool scatter(
            const Ray& r_in, const HitInfo& rec, color& attenuation, Ray& scattered
    ) const override {
        attenuation = color(1.0, 1.0, 1.0);
        double refraction_ratio = rec.front_face ? (1.0/ir) : ir;

        vec3 unit_direction = unit_vector(r_in.direction());
        double cos_theta = fmin(dot(-unit_direction, rec.m_normal), 1.0);
        double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

        bool cannot_refract = refraction_ratio * sin_theta > 1.0;
        vec3 dir;

        if (cannot_refract || reflectance(cos_theta, refraction_ratio) > rand_number()) {
            dir = reflect(unit_direction, rec.m_normal);
        } else {
            dir = refract(unit_direction, rec.m_normal, refraction_ratio);
        }


        scattered = Ray(rec.m_position, dir);
        return true;
    }

private:
    double ir; // Index of Refraction


    static double reflectance(double cosine, double ref_idx) {
        auto r0 = (1 - ref_idx) / (1 + ref_idx);
        r0 = r0 * r0;
        return r0 + (1 - r0) * pow((1 - cosine), 5);
    }
};

#endif