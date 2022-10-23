#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H

#include "ray.h"
#include "vec3.h"
#include "raytracer.h"

class Material {
    public:
        virtual bool scatter(const Ray& ray,
                             const HitInfo& hit,
                             Vector3<double>& attenuation,
                             Ray& scattered) const =0;
};

class Lambertian : public Material {
    public:
        Lambertian(const Vector3<double>& a) : m_albedo(a) {}

        virtual bool scatter(const Ray &ray, const HitInfo &hit, Vector3<double> &attenuation, Ray &scattered) const override {
            Vector3<double> scatter_dir = hit.m_normal + Vector3<double>::random_unit_vector();

            if (scatter_dir.is_zero()) {
                scatter_dir = hit.m_normal;
            }

            scattered = Ray(hit.m_position, scatter_dir);
            attenuation = m_albedo;
            return true;
        }

    private:
        Vector3<double> m_albedo;
};

class Metal : public Material {
public:
    Metal(const Vector3<double>& a) : m_albedo(a) {}

    virtual bool scatter(const Ray &ray, const HitInfo &hit, Vector3<double> &attenuation, Ray &scattered) const override {
        Vector3<double> reflected = Vector3<double>::reflect(ray.direction().normalized(), hit.m_normal);
        scattered = Ray(hit.m_position, reflected);
        attenuation = m_albedo;
        return scattered.direction().dot(hit.m_normal) > 0;
    }

private:
    Vector3<double> m_albedo;
};

#endif