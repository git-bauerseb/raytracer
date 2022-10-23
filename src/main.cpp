#include "p3.h"
#include "scene.h"

#include "objects/r_object.h"
#include "objects/sphere.h"

#include "utility.h"


int main() {


    Scene scene(512, 2.0f, 16.0f / 9.0f, 1.0f);

    RObjectList list;
    auto ground_material = std::make_shared<Lambertian>(Vector3<double>(0.8, 0.8, 0.0));
    auto center_mateiral = std::make_shared<Lambertian>(Vector3<double>(0.7, 0.3, 0.3));
    auto material_left = std::make_shared<Metal>(Vector3<double>(0.8, 0.8, 0.8));
    auto material_right = std::make_shared<Metal>(Vector3<double>(0.8, 0.6, 0.2));



    list.add(std::make_shared<Sphere>(Sphere({0, -100.5, -2}, 100.0f, ground_material)));
    list.add(std::make_shared<Sphere>(Sphere({0, 0, -2}, 0.5f, center_mateiral)));
    list.add(std::make_shared<Sphere>(Sphere({-1, 0, -2}, 0.5f, material_left)));
    list.add(std::make_shared<Sphere>(Sphere({1, 0, -2}, 0.5f, material_right)));
    scene.add_objects(list);

    auto buffer = scene.render();

    P3 p3(scene.image_width(), scene.image_height(), "../resources/img_shadow_corrected.ppm");
    p3.set_img_buffer(buffer);
    p3.write_image();


    return 0;
}
