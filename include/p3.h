#ifndef RAYTRACER_P3_H
#define RAYTRACER_P3_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "vec3.h"

class P3 {
    public:
        P3(int width, int height, std::string path);
        ~P3();

        void set_img_buffer(std::vector<Vector3<double>>& buffer);
        void write_image();

    private:
        void write_header();

        std::ofstream m_outfile;

        std::vector<Vector3<double>> m_buffer;

        int m_img_width;
        int m_img_height;
};

#endif