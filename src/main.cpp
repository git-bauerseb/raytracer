#include <iostream>
#include <thread>
#include <list>
#include <algorithm>
#include <mutex>
#include <sstream>
#include <cmath>

#include "scene.h"
#include "p3.h"

void render_scene_parallel() {
    Scene scene;
    scene.set_random_scene();
    std::vector<vec3> buffer = scene.render();

    P3 p3(scene.get_width(), scene.get_height(), "../resources/img.ppm");
    p3.set_img_buffer(buffer);
    p3.write_image();
}

int main() {
    render_scene_parallel();
    return 0;
}