#include "scene.h"


void Scene::set_structured_scene() {
    set_camera_settings_structured();

    // Blue: 83aedb
    // Red: ae6e7f

    RObjectList world;

    auto ground_material = std::make_shared<Lambertian>(color(0x66/255.0, 0x86/255.0, 0x6e/255.0));

    auto red_material = std::make_shared<Metal>(color(0xae/255.0, 0x6e/255.0, 0x7f/255.0), 0.76);
    auto blue_material = std::make_shared<Lambertian>(color(0x83/255.0, 0xae/255.0, 0xdb/255.0));
    auto silver_material = std::make_shared<Metal>(color(211.0/255.0, 211.0/255.0, 211.0/255.0), 1.0);
    auto dark_gray_material = std::make_shared<Metal>(color(98.0/255.0, 98.0/255.0, 98.0/255.0), 0.83);
    auto white_material = std::make_shared<Lambertian>(color(242.0/255.0, 242.0/255.0, 242.0/255.0));

    world.add(std::make_shared<Sphere>(vec3(0, -1000.5, 0), 1000, ground_material));

    // Middle
    world.add(std::make_shared<Sphere>(vec3(0, 0.3, 18.6), 1, blue_material));
    world.add(std::make_shared<Sphere>(vec3(2, 0.3, 17.8), 1, dark_gray_material));
    world.add(std::make_shared<Sphere>(vec3(4.0, 0.3, 17.0), 1, white_material));
    world.add(std::make_shared<Sphere>(vec3(-2, 0.3, 17.8), 1, silver_material));
    world.add(std::make_shared<Sphere>(vec3(-4.0, 0.3, 17.0), 1, red_material));


    m_objects = world;

}

void Scene::set_random_scene() {

    set_camera_settings_random();

    RObjectList world;

    auto ground_material = std::make_shared<Lambertian>(color(0x69/256.0, 0x85/256.0, 0x6e/256.0));
    world.add(std::make_shared<Sphere>(point3(0,-1000,0), 1000, ground_material));


    for (int a = -7; a < 7; a++) {
        for (int b = -7; b < 7; b++) {
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

    auto red_material = std::make_shared<Metal>(color(0xae/255.0, 0x6e/255.0, 0x7f/255.0), 0.76);
    auto blue_material = std::make_shared<Lambertian>(color(0x83/255.0, 0xae/255.0, 0xdb/255.0));
    auto silver_material = std::make_shared<Metal>(color(211.0/255.0, 211.0/255.0, 211.0/255.0), 1.0);


    world.add(std::make_shared<Sphere>(point3(2, 1, 0), 1.0, blue_material));
    world.add(std::make_shared<Sphere>(point3(4, 1, 0), 1.0, silver_material));
    world.add(std::make_shared<Sphere>(point3(6, 1, 0), 1.0, red_material));

    m_objects = world;
}

std::vector<vec3> Scene::render() {
    std::vector<vec3> buffer(m_img_height * m_img_width);
    std::vector<std::thread> threads(std::thread::hardware_concurrency());

    RenderSchedule schedule(m_img_width, m_img_height, 32);

    for (auto& t : threads) {
        t = std::thread(RenderTask{schedule, buffer, m_objects,m_camera,
                                   m_samples, m_raytrace_depth, m_img_width, m_img_height});
    }

    for (auto& t : threads) {
        t.join();
    }

    return buffer;
}

void Scene::set_camera_settings_structured() {
    const auto aspect_ratio = 16.0 / 9.0;
    m_img_width = 1280;
    m_img_height = static_cast<int>(m_img_width / aspect_ratio);
    m_samples = 128;
    m_raytrace_depth = 32;

    point3 lookfrom(0,1,0);
    point3 lookat(0,0.92,1);
    vec3 vup(0,1,0);
    auto dist_to_focus = 17;
    auto aperture = 0.0;

    m_camera = Camera(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);
}

void Scene::set_camera_settings_random() {

    const auto aspect_ratio = 16.0 / 9.0;
    m_img_width = 512;
    m_img_height = static_cast<int>(m_img_width / aspect_ratio);
    m_samples = 64;
    m_raytrace_depth = 16;

    point3 lookfrom(13,1.6,3);
    point3 lookat(0,1.4,0);
    vec3 vup(0,1,0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.1;

    m_camera = Camera(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);
}