#include "p3.h"
#include "scene.h"

#include "objects/r_object.h"
#include "objects/sphere.h"

#include "utility.h"


int main() {


    Scene scene(512, 2.0f, 16.0f / 9.0f, 1.0f);

    RObjectList list;
    list.add(std::make_shared<Sphere>(Sphere({0.2,0.4,-2}, .5f)));
    list.add(std::make_shared<Sphere>(Sphere({-0.2,0.1,-2}, 0.4f)));
    scene.add_objects(list);

    auto buffer = scene.render();

    P3 p3(scene.image_width(), scene.image_height(), "../resources/img.ppm");
    p3.set_img_buffer(buffer);
    p3.write_image();


    return 0;
}
