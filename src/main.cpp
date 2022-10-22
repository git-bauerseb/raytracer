#include "p3.h"
#include "scene.h"

#include "objects/sphere.h"

int main() {

    Scene scene(256, 2.0f, 16.0f / 9.0f, 1.0f);

    Sphere* sphere = new Sphere({0,0,-2}, .5f);
    scene.add_object(sphere);

    auto buffer = scene.render();

    P3 p3(scene.image_width(), scene.image_height(), "../resources/img.ppm");
    p3.set_img_buffer(buffer);
    p3.write_image();


    return 0;
}
