#include <SFML/Graphics.hpp>
#include <thread>
#include <mutex>

#include "objects/render_object.h"
#include "camera.h"
#include "objects/sphere.h"
#include "threading.h"
#include "math/vector3.h"

void set_scene(RenderObjectList& world, Camera& camera) {
    auto material_ground   = std::make_shared<Lambertian>(color(85.0/255.0, 139.0/255.0, 47.0/255.0));
    world.add(std::make_shared<Sphere>(point3(0, -1000, -1),1000, material_ground));

    auto material1 = std::make_shared<Lambertian>(color(0.97, 0.97, 0.97));
    auto material2 = std::make_shared<Metal>(color(0.43, 0.43, 0.43), 0.3);
    auto material3 = std::make_shared<Lambertian>(color(3.0/255.0, 169.0/255.0, 244.0/255.0));
    auto material4 = std::make_shared<Metal>(color(0.9, 0.9, 0.9), 0.0);
    auto material5 = std::make_shared<Metal>(color(194.0/255.0, 24.0/255.0, 91.0/255.0), 0.86);


    world.add(std::make_shared<Sphere>(point3(0, 1, -5),1, material3));

    world.add(std::make_shared<Sphere>(point3(-2, 1, -4.2),1, material2));
    world.add(std::make_shared<Sphere>(point3(-4, 1, -3.4),1, material1));

    world.add(std::make_shared<Sphere>(point3(2, 1, -4.2),1, material4));
    world.add(std::make_shared<Sphere>(point3(4, 1, -3.4),1, material5));

    std::vector<color> colors;
    colors.push_back({118.0/255.0, 1.0, 3.0/255.0});
    colors.push_back({0, 229.0/255.0, 1.0});
    colors.push_back({244.0/255.0, 67.0/255.0, 54.0/255.0});
    colors.push_back({1, 235.0/255.0, 59.0/255.0});
    colors.push_back({0, 200.0/255.0, 83.0/255.0});

    double startX = -1;

    for (int i = 0; i < 5; i++) {
        auto mat = std::make_shared<Dielectric>(1.5, colors[i]);
        world.add(std::make_shared<Sphere>(point3(startX, 0.2, -1.3), 0.2, mat));
        startX += 0.5;
    }

    camera = Camera(120.0);
}

int main() {

    const double aspect_ratio = 16.0 / 9.0;
    const int img_width = 1024;
    const int img_height = static_cast<int>(img_width / aspect_ratio);

    RenderSchedule schedule(img_width, img_height, 32);


    RenderObjectList world;
    Camera camera;
    set_scene(world, camera);

    std::vector<std::thread> threads(std::thread::hardware_concurrency());


    sf::RenderWindow window(sf::VideoMode(img_width, img_height), "Title");
    sf::View view = window.getDefaultView();
    view.setSize(img_width, -img_height);
    window.setView(view);

    sf::Texture texture;
    texture.create(img_width, img_height);

    auto pixels = new sf::Uint8[img_width * img_height * 4];

    texture.update(pixels);

    sf::Sprite sprite;
    sprite.setTexture(texture);


    for(auto& t : threads) {
        t = std::thread(RenderTask{schedule, pixels, world, camera, 12, 96, img_width, img_height});
    }

    while (window.isOpen()) {
        sf::Event event{};
        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        texture.update(pixels);

        window.clear();
        window.draw(sprite);
        window.display();

        sf::sleep(sf::milliseconds(1000));
    }


    for(auto& t : threads) {
        t.join();
    }

    texture.copyToImage().saveToFile("render.png");
    delete[] pixels;

    return 0;
}