#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H

#include <vector>

#include "vec3.h"
#include "ray.h"
#include "objects/r_object.h"

#include "utility.h"

class Scene {
    public:
        Scene(int img_width, double viewport_width, double aspect_ratio, double focal_length);

        std::vector<Vector3<double>> render() const;

        int image_width() const {return m_img_width;}
        int image_height() const {return m_img_height;}

        void add_objects(RObjectList& list) {
            m_render_objects = list;
        }

    private:

        Vector3<double> get_color(Ray& r, int depth) const;

        RObjectList m_render_objects;           // List of objects that can be rendered

        int m_img_width;                        // The width of the rendered image
        int m_img_height;                       // The height of the rendered image

        double m_viewport_width;                 // Width of the viewport onto which
                                                // our render is projected
        double m_viewport_height;

        double m_aspect_ration;                  // The aspect ratio of the viewport
                                                // (width / height)

        double m_focal_length;                   // Distance between camera and viewport

        Vector3<double> m_camera_pos;            // Position of camera in world coordinates
        Vector3<double> m_viewport_origin;       // Origin (bottom-left corner) of viewport

        Vector3<double> m_horizontal;            // Describes the vector (m_viewport_width, 0, 0)
        Vector3<double> m_vertical;              // Describes the vector (0, m_viewport_height, 0)
};

#endif