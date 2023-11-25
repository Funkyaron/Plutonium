


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




std::shared_ptr<Scene> createScene() {
    std::shared_ptr<Scene> result = std::make_shared<Scene>();

    std::shared_ptr<Camera> cam = std::make_shared<Camera>();
    result->setCamera(cam);

    std::shared_ptr<ShapeGroup> world = std::make_shared<ShapeGroup>();
    std::shared_ptr<Sphere> mySphere = std::make_shared<Sphere>(Vector3(0.0, 0.0, -1.5), 0.5, std::make_shared<Lambert>(Color(0.5, 0.5, 0.5)));
    world->addShape(mySphere);
    mySphere = std::make_shared<Sphere>(Vector3(0, -100.5, -1), 100, std::make_shared<Lambert>(Color(0.5, 0.8, 0.5)));
    world->addShape(mySphere);
    mySphere = std::make_shared<Sphere>(Vector3(-1.5, 0.0, -2.0), 0.4, std::make_shared<Metal>(Color(0.8, 0.5, 0.5), 0.1));
    world->addShape(mySphere);
    mySphere = std::make_shared<Sphere>(Vector3(1.1, 0.0, -1.5), 0.5, std::make_shared<Metal>(Color(0.5, 0.5, 0.8), 0.7));
    world->addShape(mySphere);
    result->setWorldShape(world);

    return result;
}




int main() {

    std::shared_ptr<Scene> myScene = createScene();

    PixelBuffer myImage;

    Plutonium::renderScene(myScene, myImage);

    unsigned char * pixelData = new unsigned char[myImage.getWidth() * myImage.getHeight() * 3];

    myImage.forEach([&](int x, int y, Color& currentPixel) {
        pixelData[3 * (x + myImage.getWidth() * y) + 0] = (unsigned char)(255.99 * std::clamp(currentPixel.r(), 0.0f, 1.0f));
        pixelData[3 * (x + myImage.getWidth() * y) + 1] = (unsigned char)(255.99 * std::clamp(currentPixel.g(), 0.0f, 1.0f));
        pixelData[3 * (x + myImage.getWidth() * y) + 2] = (unsigned char)(255.99 * std::clamp(currentPixel.b(), 0.0f, 1.0f));
    });

    stbi_write_png("../Results/image.png", myImage.getWidth(), myImage.getHeight(), 3, pixelData, 0);

    delete pixelData;

    return 0;
}