#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include "math/vector3.h"
#include "ray.h"
#include "utility.h"

class Camera {
    public:
        Camera() {}
        Camera(double vfov) {
            auto aspect_ratio = 16.0 / 9.0;
            auto viewport_height = 2.0;// * h;
            auto viewport_width = aspect_ratio * viewport_height;
            auto focal_length = 1.0;

            origin = point3(0,0.7,0);
            horizontal = Vector3(viewport_width, 0.0, 0.0);
            vertical = Vector3(0.0, viewport_height, 0.0);
            lower_left_corner = origin
                                - horizontal / 2
                                - vertical / 2
                                - Vector3(0, 0, focal_length);
        }

        Ray get_ray(double u, double v) const {
            return Ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
        }


    private:
        Vector3 origin;
        Vector3 lower_left_corner;
        Vector3 horizontal;
        Vector3 vertical;
};

#endif
