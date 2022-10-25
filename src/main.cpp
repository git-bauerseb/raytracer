#include "p3.h"
#include "scene.h"

#include "objects/r_object.h"
#include "objects/sphere.h"

#include "utility.h"

void setup_scene(Scene& scene) {
    RObjectList world;

    auto material_ground = std::make_shared<Lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = std::make_shared<Dielectric>(1.5);
    auto material_left = std::make_shared<Dielectric>(1.5);
    auto material_right = std::make_shared<Metal>(color(0.8, 0.6, 0.2), 1.0);


    world.add(std::make_shared<Sphere>(point3(0.0, -100.5, -2.0), 100.0, material_ground));
    world.add(std::make_shared<Sphere>(point3(0.0, 0.0, -2.0), 0.5, material_center));
    world.add(std::make_shared<Sphere>(point3(-1.0, 0.0, -2.0), 0.5, material_left));
    world.add(std::make_shared<Sphere>(point3(1.0, 0.0, -2.0), 0.5, material_right));

    scene.add_objects(world);
}

int main() {


    Scene scene(512, 2.0f, 16.0 / 9.0, 1.0);

    setup_scene(scene);
    auto buffer = scene.render();

    P3 p3(scene.image_width(), scene.image_height(), "../resources/img_dielectric.ppm");
    p3.set_img_buffer(buffer);
    p3.write_image();


    return 0;
}
