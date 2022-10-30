#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H

#include <iostream>
#include <mutex>
#include <thread>

#include "objects/r_object.h"
#include "objects/sphere.h"

#include "material.h"
#include "camera.h"

class Scene {

    public:
        Scene() {}

        // Set up a random scene
        void set_random_scene();
        void set_structured_scene();
        std::vector<vec3> render();

        int get_width() const {return m_img_width;}
        int get_height() const {return m_img_height;}

    private:
        void set_camera_settings_random();
        void set_camera_settings_structured();

        Camera m_camera;
        RObjectList m_objects;

        int m_img_height;
        int m_img_width;

        int m_samples;
        int m_raytrace_depth;
};

class RenderSchedule {
public:
    RenderSchedule(int img_width, int img_height, int block_size)
            : m_img_width(img_width), m_img_height(img_height),
              m_block_size(block_size), m_curr_idx(0) {

        int num_h = (img_width / block_size);
        if (img_width % block_size != 0) {num_h++;}

        int num_v = (img_height / block_size);
        if (img_height % block_size != 0) {num_v++;}

        m_num_blocks_hor = num_h;
        m_num_blocks_ver = num_v;

    }

    bool has_next_region() {
        m_mutex.lock();
        bool result = m_curr_idx < (m_num_blocks_hor * m_num_blocks_ver);
        m_mutex.unlock();
        return result;
    }

    void next_region(int& x, int& y, int& width, int& height) {
        m_mutex.lock();
        int block_x = (m_curr_idx) % m_num_blocks_hor;
        int block_y = (m_curr_idx - block_x) / m_num_blocks_hor;

        x = m_block_size * block_x;
        y = m_block_size * block_y;

        width = std::min(m_block_size, m_img_width - x);
        height = std::min(m_block_size, m_img_height - y);

        std::cout << m_curr_idx << "/" << (m_num_blocks_hor * m_num_blocks_ver) << "\n";

        m_curr_idx++;
        m_mutex.unlock();
    }

private:
    int m_curr_idx;
    int m_img_width;
    int m_img_height;
    int m_block_size;
    // The most recent block processed

    int m_num_blocks_hor;   // Number of blocks in one row to be processed
    int m_num_blocks_ver;   // Number of blocks in one column

    std::mutex m_mutex;
};

class RenderTask {
    public:
        RenderTask(RenderSchedule& schedule, std::vector<vec3>& buffer,
                   RObjectList& objects, Camera& camera, int depth, int samples, int img_width, int img_height)
            : m_scheduler(schedule),
              m_buffer(buffer),
              m_objects(objects),
              m_camera(camera),
              m_samples(samples),
              m_raytrace_depth(depth),
              m_img_width(img_width),
              m_img_height(img_height) {}

        void operator()() {
            while(m_scheduler.has_next_region()) {
                int x,y,width,height;
                m_scheduler.next_region(x,y,width,height);
                render_region(x,y,width,height);
            }
        }

    private:
        color ray_color(const Ray& r, int depth) {
            HitInfo rec;

            // If we've exceeded the ray bounce limit, no more light is gathered.
            if (depth <= 0)
                return color(0,0,0);

            if (m_objects.hit(r, 0.001, std::numeric_limits<double>::infinity(), rec)) {
                Ray scattered;
                color attenuation;
                if (rec.m_material->scatter(r, rec, attenuation, scattered))
                    return attenuation * ray_color(scattered, depth-1);
                return color(0,0,0);
            }

            vec3 unit_direction = unit_vector(r.direction());
            auto t = 0.5*(unit_direction.y() + 1.0);
            return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
        }

        void render_region(int x, int y, int width, int height) {
            for (int j = y; j < y + height; j++) {
                int idx = x + j * m_img_width;
                for (int i = x; i < x + width; i++, idx++) {
                    color pixel_color(0,0,0);
                    for (int s = 0; s < m_samples; ++s) {
                        auto u = (i + rand_number()) / (m_img_width-1);
                        auto v = (j + rand_number()) / (m_img_height-1);
                        Ray r = m_camera.get_ray(u, v);
                        pixel_color += ray_color(r, m_raytrace_depth);
                    }

                    double r = pixel_color.x();
                    double g = pixel_color.y();
                    double b = pixel_color.z();

                    const double scale = 1.0 / m_samples;

                    r = std::sqrt(r * scale);
                    g = std::sqrt(g * scale);
                    b = std::sqrt(b * scale);
                    m_buffer[idx] = vec3(r,g,b);
                }
            }
        }

        RenderSchedule& m_scheduler;
        RObjectList& m_objects;
        std::vector<vec3>& m_buffer;
        Camera& m_camera;

        int m_samples;
        int m_raytrace_depth;

        int m_img_width;
        int m_img_height;
};

#endif
