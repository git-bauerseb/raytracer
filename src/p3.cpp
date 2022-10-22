#include "p3.h"

// Public methods
P3::P3(int width, int height, std::string path)
    : m_img_height(height), m_img_width(width) {
    m_outfile.open(path);
}

P3::~P3() {
    if (m_outfile) {
        m_outfile.close();
    }
}

void P3::write_image() {
    this->write_header();

    for (int y = 0; y < m_img_height; y++) {
        for (int x = 0; x < m_img_width; x++) {
            Vector3<float> vec = m_buffer[x + m_img_width * y];
            m_outfile << static_cast<int>(255.999 * vec[0]) << " "
                      << static_cast<int>(255.999 * vec[1]) << " "
                      << static_cast<int>(255.999 * vec[2]) << " ";
        }

        m_outfile << "\n";
    }
}

void P3::set_img_buffer(std::vector<Vector3<float>> &buffer) {
    m_buffer = std::move(buffer);
}


// Private methods
void P3::write_header() {
    m_outfile << "P3\n";
    m_outfile << m_img_width << " " << m_img_height << "\n";
    m_outfile << "255\n";
}