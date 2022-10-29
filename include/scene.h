#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H

#include <iostream>

#include "objects/r_object.h"
#include "objects/sphere.h"

#include "material.h"
#include "camera.h"

class Scene {

    public:
        Scene() {}

        // Set up a random scene
        void set_random_scene();
        std::vector<vec3> render();

        int get_width() const {return m_img_width;}
        int get_height() const {return m_img_height;}

    private:
        void set_camera_settings();

        color ray_color(const Ray& r, int depth);

        Camera m_camera;
        RObjectList m_objects;

        int m_img_height;
        int m_img_width;

        int m_samples;
        int m_raytrace_depth;
};

#endif
