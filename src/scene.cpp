#include "scene.h"

void Scene::set_random_scene() {

    set_camera_settings();

    RObjectList world;

    auto ground_material = std::make_shared<Lambertian>(color(0.5, 0.5, 0.5));
    world.add(std::make_shared<Sphere>(point3(0,-1000,0), 1000, ground_material));


    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = rand_number();
            point3 center(a + 0.9*rand_number(), 0.2, b + 0.9*rand_number());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                std::shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = std::make_shared<Lambertian>(albedo);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = rand_number(0, 0.5);
                    sphere_material = std::make_shared<Metal>(albedo, fuzz);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = std::make_shared<Dielectric>(1.5);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<Dielectric>(1.5);
    world.add(std::make_shared<Sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<Lambertian>(color(0.4, 0.2, 0.1));
    world.add(std::make_shared<Sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<Metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(std::make_shared<Sphere>(point3(4, 1, 0), 1.0, material3));

    m_objects = world;
}

std::vector<vec3> Scene::render() {
    std::vector<vec3> buffer(m_img_height * m_img_width);

    int idx = 0;
    for (int j = m_img_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < m_img_width; ++i, idx++) {
            color pixel_color(0,0,0);
            for (int s = 0; s < m_samples; ++s) {
                auto u = (i + rand_number()) / (m_img_width-1);
                auto v = (j + rand_number()) / (m_img_height-1);
                Ray r = m_camera.get_ray(u, v);
                pixel_color += ray_color(r, m_raytrace_depth);
            }

            double r = pixel_color.x();
            double g = pixel_color.y();
            double b = pixel_color.z();

            const double scale = 1.0 / m_samples;

            r = std::sqrt(r * scale);
            g = std::sqrt(g * scale);
            b = std::sqrt(b * scale);
            buffer[idx] = vec3(r,g,b);
        }
    }

    return buffer;
}



// Private
color Scene::ray_color(const Ray& r, int depth) {
    HitInfo rec;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return color(0,0,0);

    if (m_objects.hit(r, 0.001, std::numeric_limits<double>::infinity(), rec)) {
        Ray scattered;
        color attenuation;
        if (rec.m_material->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, depth-1);
        return color(0,0,0);
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

void Scene::set_camera_settings() {

    const auto aspect_ratio = 16.0 / 9.0;
    m_img_width = 256;
    m_img_height = static_cast<int>(m_img_width / aspect_ratio);
    m_samples = 38;
    m_raytrace_depth = 8;

    point3 lookfrom(13,1.6,3);
    point3 lookat(0,1.4,0);
    vec3 vup(0,1,0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.1;

    m_camera = Camera(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);
}