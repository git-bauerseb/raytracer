#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H

#include <vector>

#include "vec3.h"
#include "ray.h"
#include "objects/r_object.h"

class Scene {
    public:
        Scene(int img_width, float viewport_width, float aspect_ratio, float focal_length);

        std::vector<Vector3<float>> render() const;

        int image_width() const {return m_img_width;}
        int image_height() const {return m_img_height;}

        void add_object(RObject* obj);

    private:

        Vector3<float> get_color(Ray& r) const;

        std::vector<RObject*> m_render_objects;

        int m_img_width;                        // The width of the rendered image
        int m_img_height;                       // The height of the rendered image

        float m_viewport_width;                 // Width of the viewport onto which
                                                // our render is projected
        float m_viewport_height;

        float m_aspect_ration;                  // The aspect ratio of the viewport
                                                // (width / height)

        float m_focal_length;                   // Distance between camera and viewport

        Vector3<float> m_camera_pos;            // Position of camera in world coordinates
        Vector3<float> m_viewport_origin;       // Origin (bottom-left corner) of viewport

        Vector3<float> m_horizontal;            // Describes the vector (m_viewport_width, 0, 0)
        Vector3<float> m_vertical;              // Describes the vector (0, m_viewport_height, 0)
};

#endif