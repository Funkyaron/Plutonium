


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
#include "Transform.h"






std::shared_ptr<Scene> createScene() {
    std::shared_ptr<Scene> result = std::make_shared<Scene>();

    std::shared_ptr<Camera> cam = std::make_shared<Camera>();
    cam->setResolution(800, 600);
    cam->setLookFrom(Vector3(8.0, 2.0, 3.0));
    cam->setLookAt(Vector3(0.0, 1.0, 0.0));
    cam->setVerticalUp(Vector3(0.0, 1.0, 0.0));
    cam->setVerticalFOV(40.0);
    cam->setAperture(0.3);
    cam->setFocusDist((Vector3(8.0, 2.0, 2.0) - Vector3(0.0, 1.0, 0.0)).length());
    result->setCamera(cam);

    std::shared_ptr<Geometry> sphereGeometry = std::make_shared<Sphere>();

    std::shared_ptr<ShapeGroup> world = std::make_shared<ShapeGroup>();

    std::shared_ptr<GeometryInstance> floorSphere = std::make_shared<GeometryInstance>();
    floorSphere->setGeometry(sphereGeometry);
    floorSphere->getTransform()->setLocationY(-1000.0);
    floorSphere->getTransform()->setUniformScale(1000.0);
    floorSphere->setMaterial(std::make_shared<Lambert>(Color(0.5, 0.5, 0.5)));

    world->addShape(floorSphere);

    for(int a = -11; a < 11; a++) {
        for(int b = -11; b < 11; b++) {
            float chooseMat = Plutonium::getRandomNumber();
            Vector3 center(a + 0.9 * Plutonium::getRandomNumber(), 0.3, b + 0.9 * Plutonium::getRandomNumber());
            if((center - Vector3(4.0, 0.2, 0.0)).length() > 0.9) {
                std::shared_ptr<GeometryInstance> currentSphere = std::make_shared<GeometryInstance>();
                currentSphere->setGeometry(sphereGeometry);
                currentSphere->getTransform()->setLocationX(center.x());
                currentSphere->getTransform()->setLocationY(center.y());
                currentSphere->getTransform()->setLocationZ(center.z());
                currentSphere->getTransform()->setRotationX(360.0 * Plutonium::getRandomNumber());
                currentSphere->getTransform()->setRotationY(360.0 * Plutonium::getRandomNumber());
                currentSphere->getTransform()->setRotationZ(360.0 * Plutonium::getRandomNumber());
                currentSphere->getTransform()->setScaleX(0.1 + 0.2 * Plutonium::getRandomNumber());
                currentSphere->getTransform()->setScaleY(0.1 + 0.2 * Plutonium::getRandomNumber());
                currentSphere->getTransform()->setScaleZ(0.1 + 0.2 * Plutonium::getRandomNumber());
                if(chooseMat < 0.8) {
                    currentSphere->setMaterial(std::make_shared<Lambert>(Color(Plutonium::getRandomNumber() * Plutonium::getRandomNumber(), Plutonium::getRandomNumber() * Plutonium::getRandomNumber(), Plutonium::getRandomNumber() * Plutonium::getRandomNumber())));
                }
                else if(chooseMat < 0.95) {
                    currentSphere->setMaterial(std::make_shared<Metal>(Color(0.5 * (1.0 + Plutonium::getRandomNumber()), 0.5 * (1.0 + Plutonium::getRandomNumber()), 0.5 * (1.0 + Plutonium::getRandomNumber())), 0.5 * Plutonium::getRandomNumber()));
                }
                else {
                    currentSphere->setMaterial(std::make_shared<Dielectric>(1.5));
                }

                world->addShape(currentSphere);
            }
        }
    }

    std::shared_ptr<GeometryInstance> bigSphere1 = std::make_shared<GeometryInstance>();
    bigSphere1->setGeometry(sphereGeometry);
    bigSphere1->getTransform()->setLocationY(1.0);
    bigSphere1->setMaterial(std::make_shared<Dielectric>(1.5));
    world->addShape(bigSphere1);

    std::shared_ptr<GeometryInstance> bigSphere2 = std::make_shared<GeometryInstance>();
    bigSphere2->setGeometry(sphereGeometry);
    bigSphere2->getTransform()->setLocationX(-4.0);
    bigSphere2->getTransform()->setLocationY(1.0);
    bigSphere2->setMaterial(std::make_shared<Lambert>(Color(0.4, 0.2, 0.1)));
    world->addShape(bigSphere2);

    std::shared_ptr<GeometryInstance> bigSphere3 = std::make_shared<GeometryInstance>();
    bigSphere3->setGeometry(sphereGeometry);
    bigSphere3->getTransform()->setLocationX(4.0);
    bigSphere3->getTransform()->setLocationY(1.0);
    bigSphere3->setMaterial(std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0));
    world->addShape(bigSphere3);

    result->setWorldShape(world);

    return result;
}


// std::shared_ptr<Scene> createScene() {
//     std::shared_ptr<Scene> result = std::make_shared<Scene>();

//     std::shared_ptr<Camera> cam = std::make_shared<Camera>();
//     cam->setLookFrom(Vector3(0.0, 0.0, 3.0));
//     cam->setLookAt(Vector3(0.0, 0.0, 0.0));
//     result->setCamera(cam);


//     std::shared_ptr<Geometry> sphereGeometry = std::make_shared<Sphere>();

//     std::shared_ptr<GeometryInstance> sphere1 = std::make_shared<GeometryInstance>();
//     sphere1->setGeometry(sphereGeometry);
//     sphere1->getTransform()->setLocationX(-2.2);
//     sphere1->getTransform()->setLocationZ(1.0);
//     sphere1->getTransform()->setUniformScale(0.8);
//     sphere1->setMaterial(std::make_shared<Lambert>(Color(0.0, 1.0, 0.0)));

//     std::shared_ptr<GeometryInstance> ellipsoid1 = std::make_shared<GeometryInstance>();
//     ellipsoid1->setGeometry(sphereGeometry);
//     ellipsoid1->getTransform()->setLocationX(2.0);
//     ellipsoid1->getTransform()->setRotationZ(45.0);
//     ellipsoid1->getTransform()->setScaleX(2.0);
//     ellipsoid1->setMaterial(std::make_shared<Metal>(Color(0.8, 0.8, 0.8), 0.1));

//     std::shared_ptr<ShapeGroup> world = std::make_shared<ShapeGroup>();
//     world->addShape(sphere1);
//     world->addShape(ellipsoid1);
//     result->setWorldShape(world);

//     return result;
// }




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