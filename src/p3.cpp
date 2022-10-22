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
            Vector3<int> vec = m_buffer[x + m_img_width * y];
            m_outfile << vec[0] << " " << vec[1] << " " << vec[2] << " ";
        }

        m_outfile << "\n";
    }
}

void P3::set_img_buffer(std::vector<Vector3<int>> &buffer) {
    m_buffer = std::move(buffer);
}


// Private methods
void P3::write_header() {
    m_outfile << "P3\n";
    m_outfile << m_img_width << " " << m_img_height << "\n";
    m_outfile << "255\n";
}