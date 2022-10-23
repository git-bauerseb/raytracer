#include "scene.h"

Scene::Scene(int img_width, double viewport_width, double aspect_ratio, double focal_length) {
    m_img_width = img_width;
    m_viewport_width = viewport_width;
    m_focal_length = focal_length;

    m_viewport_height = (1.0f / aspect_ratio) * m_viewport_width;
    m_img_height = static_cast<int>((1.0f / aspect_ratio) * m_img_width);

    m_horizontal = Vector3<double>(m_viewport_width, 0, 0);
    m_vertical = Vector3<double>(0, m_viewport_height, 0);

    m_viewport_origin = -0.5f * m_horizontal
                        - 0.5f * m_vertical
                        - Vector3<double>(0, 0, focal_length);
}

Vector3<double> Scene::get_color(Ray& r, int depth) const {
    HitInfo info;

    if (depth <= 0) {
        return {0,0,0};
    }

    if (m_render_objects.hit(r, info, 0, std::numeric_limits<double>::max())) {
            Vector3<double> target = info.m_position + info.m_normal + Vector3<double>::random_in_unit_sphere();
            Ray n_r(info.m_position, target - info.m_position);
            return 0.5 * Scene::get_color(n_r, depth-1);
    }

    Vector3<double> norm = r.direction().normalized();
    double t = 0.5f * (norm[1] + 1.0);
    return (1.0f - t) * Vector3<double>(1.0, 1.0, 1.0)
            + t * Vector3<double>(0.5, 0.7, 1.0);
}

std::vector<Vector3<double>> Scene::render() const {
    std::vector<Vector3<double>> buffer(m_img_height * m_img_width);


    for (int y = m_img_height - 1, idx = 0; y >= 0; y--) {
        for (int x = 0; x < m_img_width; x++, idx++) {

            Vector3<double> color;

            // Anti-aliasing
            // Sample color from neighbouring pixels and average them
            for (int i = 0; i < 28; i++) {
                double u_coord = double(x + rand_number()) / (m_img_width-1);
                double v_coord = double(y + rand_number()) / (m_img_height-1);
                Ray r(m_camera_pos, m_viewport_origin + u_coord * m_horizontal + v_coord * m_vertical - m_camera_pos);
                color = color + get_color(r, 12);
            }

            double scale = 1/12.0f;

            buffer[idx][0] = std::sqrt(scale * color[0]);
            buffer[idx][1] = std::sqrt(scale * color[1]);
            buffer[idx][2] = std::sqrt(scale * color[2]);
        }
    }

    return buffer;
}