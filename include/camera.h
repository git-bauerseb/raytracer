#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include "utility.h"
#include "vec3.h"
#include "ray.h"

class Camera {
    public:
        Camera() {}

        Camera(point3 origin,
               point3 view_dir,
               vec3 up_vec,
               double vert_fov,
               double aspect_ratio,
               double aperture,
               double focus_dist) {

            double theta = deg2rad(vert_fov);
            double h = std::tan(theta / 2);
            double viewport_height = 2.0 * h;
            double viewport_width = aspect_ratio * viewport_height;

            m_w = unit_vector(origin - view_dir);
            m_u = unit_vector(cross(up_vec, m_w));
            m_v = cross(m_w, m_u);

            m_origin = origin;
            m_viewport_horizontal = focus_dist * viewport_width * m_u;
            m_viewport_vertical = focus_dist * viewport_height * m_v;
            m_viewport_origin = m_origin - m_viewport_horizontal / 2
                                - m_viewport_vertical / 2 - focus_dist * m_w;
            lens_radius = aperture / 2;
        }

        Ray get_ray(double s, double t) const {
            vec3 rd = lens_radius * random_in_unit_disk();
            vec3 offset = m_u * rd.x() + m_v * rd.y();
            return Ray(m_origin + offset,
                       m_viewport_origin + s * m_viewport_horizontal
                       + t * m_viewport_vertical - m_origin - offset
            );
        }


    private:
        point3 m_origin;
        point3 m_viewport_origin;
        vec3 m_viewport_horizontal;
        vec3 m_viewport_vertical;

        double lens_radius;

        vec3 m_u;
        vec3 m_v;
        vec3 m_w;
};

#endif