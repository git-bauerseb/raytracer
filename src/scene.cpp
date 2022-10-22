#include "scene.h"

Scene::Scene(int img_width, float viewport_width, float aspect_ratio, float focal_length) {
    m_img_width = img_width;
    m_viewport_width = viewport_width;
    m_focal_length = focal_length;

    m_viewport_height = (1.0f / aspect_ratio) * m_viewport_width;
    m_img_height = static_cast<int>((1.0f / aspect_ratio) * m_img_width);

    m_horizontal = Vector3<float>(m_viewport_width, 0, 0);
    m_vertical = Vector3<float>(0, m_viewport_height, 0);

    m_viewport_origin = -0.5f * m_horizontal
                        - 0.5f * m_vertical
                        - Vector3<float>(0, 0, focal_length);
}


Vector3<float> Scene::get_color(Ray& r) const {
    Vector3<float> norm = r.direction().normalized();
    float t = 0.5f * (norm[1] + 1.0);
    return (1.0f - t) * Vector3<float>(1.0, 1.0, 1.0)
            + t * Vector3<float>(0.5, 0.7, 1.0);
}

std::vector<Vector3<float>> Scene::render() const {
    std::vector<Vector3<float>> buffer(m_img_height * m_img_width);

    for (int y = m_img_height - 1, idx = 0; y >= 0; y--) {
        for (int x = 0; x < m_img_width; x++, idx++) {

            float u_coord = float(x) / (m_img_width-1);
            float v_coord = float(y) / (m_img_height-1);
            Ray r(m_camera_pos, m_viewport_origin + u_coord * m_horizontal + v_coord * m_vertical - m_camera_pos);
            Vector3<float> color = get_color(r);
            buffer[idx] = color;
        }
    }

    return buffer;
}