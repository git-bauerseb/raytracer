#include <iostream>
#include "scene.h"

Scene::Scene(int img_width, double viewport_height, double aspect_ratio, double focal_length) {

    m_img_width = img_width;
    m_img_height = static_cast<int>(m_img_width / aspect_ratio);

    m_viewport_height = viewport_height;
    m_viewport_width = aspect_ratio * m_viewport_height;

    m_focal_length = focal_length;


    m_horizontal = vec3(m_viewport_width, 0, 0);
    m_vertical = vec3(0, m_viewport_height, 0);

    m_camera_pos = vec3(0,0,0);
    m_viewport_origin = vec3(0,0,0)
                        - m_horizontal / 2
                        - m_vertical / 2
                        - vec3(0, 0, focal_length);
}

vec3 Scene::get_color(const Ray& r, int depth) const {
    HitInfo info;

    if (depth <= 0) {
        return vec3(0,0,0);
    }

    if (m_render_objects.hit(r, info, 0.001, std::numeric_limits<double>::infinity())) {
        vec3 target = info.m_position + random_in_hemisphere(info.m_normal);
        return 0.5 * get_color(Ray(info.m_position, target - info.m_position), depth-1);
    }

    auto unit_dir = unit_vector(r.direction());
    double t = 0.5 * (unit_dir.y() + 1.0);
    return (1.0 - t) * vec3(1.0, 1.0, 1.0)
            + t * vec3(0.5, 0.7, 1.0);
}

std::vector<vec3> Scene::render() const {
    std::vector<vec3> buffer(m_img_height * m_img_width);

    for (int y = m_img_height - 1, idx = 0; y >= 0; y--) {
        for (int x = 0; x < m_img_width; x++, idx++) {

            vec3 color;

            // Anti-aliasing
            // Sample color from neighbouring pixels and average them

            for (int i = 0; i < 64; i++) {
                double u_coord = (x + rand_number()) / (m_img_width-1);
                double v_coord = (y + rand_number()) / (m_img_height-1);
                Ray r(m_camera_pos, m_viewport_origin + u_coord * m_horizontal + v_coord * m_vertical - m_camera_pos);
                color += get_color(r, 5);
            }

            double scale = 1/64.0;

            buffer[idx][0] = std::sqrt(scale * color[0]);
            buffer[idx][1] = std::sqrt(scale * color[1]);
            buffer[idx][2] = std::sqrt(scale * color[2]);

        }
    }

    return buffer;
}