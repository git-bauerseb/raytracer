#include "p3.h"
#include "vec3.h"

std::vector<Vector3<int>> create_img(const int width, const int height) {
    std::vector<Vector3<int>> buffer(width * height);

    for (int j = height - 1, idx = 0; j >= 0; j--) {
        for (int i = 0; i < width; i++, idx++) {
            double r = double(i) / (width - 1);
            double g = double(j) / (height - 1);
            double b = 0.25;

            int ir = static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.999 * b);

            buffer[idx][0] = ir;
            buffer[idx][1] = ig;
            buffer[idx][2] = ib;
        }
    }

    return buffer;
}

int main() {
    const int img_width = 128;
    const int img_height = 128;

    std::vector<Vector3<int>> buffer = create_img(img_width, img_height);

    P3 p3(img_width, img_height, "../resources/img.ppm");
    p3.set_img_buffer(buffer);

    p3.write_image();

    return 0;
}
