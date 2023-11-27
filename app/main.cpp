


#include <algorithm>
#include <memory>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "PixelBuffer.h"
#include "Color.h"
#include "Renderer.h"
#include "Scene.h"
#include "Camera.h"
#include "Shape.h"
#include "Material.h"
#include "Utility.h"




// std::shared_ptr<Scene> createScene() {
//     std::shared_ptr<Scene> result = std::make_shared<Scene>();

//     std::shared_ptr<Camera> cam = std::make_shared<Camera>();
//     cam->setResolution(200, 100);
//     cam->setLookFrom(Vector3(2.0, 1.0, 0.0));
//     cam->setLookAt(Vector3(0.0, 0.0, -1.0));
//     cam->setVerticalUp(Vector3(0.0, 1.0, 0.0));
//     cam->setVerticalFOV(50.0);
//     cam->setAperture(0.3);
//     cam->setFocusDist((Vector3(2.0, 1.0, 0.0) - Vector3(0.0, 0.0, -1.0)).length());
//     result->setCamera(cam);

//     std::shared_ptr<ShapeGroup> world = std::make_shared<ShapeGroup>();
//     std::shared_ptr<Sphere> mySphere = std::make_shared<Sphere>(Vector3(0.0, 0.0, -1.5), 0.5, std::make_shared<Lambert>(Color(0.5, 0.5, 0.5)));
//     world->addShape(mySphere);
//     mySphere = std::make_shared<Sphere>(Vector3(0, -100.5, -1), 100, std::make_shared<Lambert>(Color(0.5, 0.8, 0.5)));
//     world->addShape(mySphere);
//     mySphere = std::make_shared<Sphere>(Vector3(-1.5, 0.0, -2.0), 0.4, std::make_shared<Metal>(Color(0.8, 0.5, 0.5), 0.1));
//     world->addShape(mySphere);
//     mySphere = std::make_shared<Sphere>(Vector3(1.1, 0.0, -1.5), 0.5, std::make_shared<Dielectric>(1.5));
//     world->addShape(mySphere);
//     result->setWorldShape(world);

//     return result;
// }


// std::shared_ptr<Scene> createScene() {
//     std::shared_ptr<Scene> result = std::make_shared<Scene>();

//     std::shared_ptr<Camera> cam = std::make_shared<Camera>();
//     cam->setResolution(800, 600);
//     cam->setLookFrom(Vector3(8.0, 2.0, 3.0));
//     cam->setLookAt(Vector3(0.0, 1.0, 0.0));
//     cam->setVerticalUp(Vector3(0.0, 1.0, 0.0));
//     cam->setVerticalFOV(40.0);
//     cam->setAperture(0.3);
//     cam->setFocusDist((Vector3(8.0, 2.0, 2.0) - Vector3(0.0, 1.0, 0.0)).length());
//     result->setCamera(cam);

//     std::shared_ptr<ShapeGroup> world = std::make_shared<ShapeGroup>();
//     int n = 500;
//     world->addShape(std::make_shared<Sphere>(Vector3(0.0, -1000.0, 0.0), 1000.0, std::make_shared<Lambert>(Color(0.5, 0.5, 0.5))));
//     int i = 1;
//     for(int a = -11; a < 11; a++) {
//         for(int b = -11; b < 11; b++) {
//             float chooseMat = Plutonium::getRandomNumber();
//             Vector3 center(a + 0.9 * Plutonium::getRandomNumber(), 0.2, b + 0.9 * Plutonium::getRandomNumber());
//             if((center - Vector3(4.0, 0.2, 0.0)).length() > 0.9) {
//                 if(chooseMat < 0.8) {
//                     world->addShape(std::make_shared<Sphere>(center, 0.2, std::make_shared<Lambert>(Color(Plutonium::getRandomNumber() * Plutonium::getRandomNumber(), Plutonium::getRandomNumber() * Plutonium::getRandomNumber(), Plutonium::getRandomNumber() * Plutonium::getRandomNumber()))));
//                 }
//                 else if(chooseMat < 0.95) {
//                     world->addShape(std::make_shared<Sphere>(center, 0.2, std::make_shared<Metal>(Color(0.5 * (1.0 + Plutonium::getRandomNumber()), 0.5 * (1.0 + Plutonium::getRandomNumber()), 0.5 * (1.0 + Plutonium::getRandomNumber())), 0.5 * Plutonium::getRandomNumber())));
//                 }
//                 else {
//                     world->addShape(std::make_shared<Sphere>(center, 0.2, std::make_shared<Dielectric>(1.5)));
//                 }
//             }
//         }
//     }
//     world->addShape(std::make_shared<Sphere>(Vector3(0.0, 1.0, 0.0), 1.0, std::make_shared<Dielectric>(1.5)));
//     world->addShape(std::make_shared<Sphere>(Vector3(-4.0, 1.0, 0.0), 1.0, std::make_shared<Lambert>(Color(0.4, 0.2, 0.1))));
//     world->addShape(std::make_shared<Sphere>(Vector3(4.0, 1.0, 0.0), 1.0, std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0)));

//     result->setWorldShape(world);

//     return result;
// }


std::shared_ptr<Scene> createScene() {
    std::shared_ptr<Scene> result = std::make_shared<Scene>();

    std::shared_ptr<Camera> cam = std::make_shared<Camera>();
    cam->setLookFrom(Vector3(0.0, 0.0, 3.0));
    cam->setLookAt(Vector3(0.0, 0.0, 0.0));
    result->setCamera(cam);

    std::shared_ptr<ShapeGroup> world = std::make_shared<ShapeGroup>();
    world->addShape(std::make_shared<Sphere>(Vector3(-2.2, 0.0, 1.0), 0.8, std::make_shared<Lambert>(Color(0.0, 1.0, 0.0))));
    world->addShape(std::make_shared<SphereInstance>());
    // world->addShape(std::make_shared<Sphere>(Vector3(0.0, 0.0, 0.0), 1.0, std::make_shared<Metal>(Color(1.0, 0.6, 0.6), 0.1)));
    result->setWorldShape(world);

    return result;
}




int main() {

    std::shared_ptr<Scene> myScene = createScene();

    PixelBuffer myImage;

    Plutonium::renderScene(myScene, myImage);

    unsigned char * pixelData = new unsigned char[myImage.getWidth() * myImage.getHeight() * 3];

    myImage.forEach([&](int x, int y, Color& currentPixel) {
        pixelData[3 * (x + myImage.getWidth() * y) + 0] = (unsigned char)(255.99 * sqrt(std::clamp(currentPixel.r(), 0.0f, 1.0f)));
        pixelData[3 * (x + myImage.getWidth() * y) + 1] = (unsigned char)(255.99 * sqrt(std::clamp(currentPixel.g(), 0.0f, 1.0f)));
        pixelData[3 * (x + myImage.getWidth() * y) + 2] = (unsigned char)(255.99 * sqrt(std::clamp(currentPixel.b(), 0.0f, 1.0f)));
    });

    stbi_write_png("../Results/image.png", myImage.getWidth(), myImage.getHeight(), 3, pixelData, 0);

    delete pixelData;

    return 0;
}