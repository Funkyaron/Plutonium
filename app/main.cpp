


#include <algorithm>
#include <memory>
#include <iostream>
#include <fstream>

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
#include "Mesh.h"






// std::shared_ptr<Scene> createScene() {
//     std::shared_ptr<Scene> result = std::make_shared<Scene>();

//     std::shared_ptr<Camera> cam = std::make_shared<Camera>();
//     cam->setResolution(200, 150);
//     cam->setLookFrom(Vector3(8.0, 2.0, 3.0));
//     cam->setLookAt(Vector3(0.0, 1.0, 0.0));
//     cam->setVerticalUp(Vector3(0.0, 1.0, 0.0));
//     cam->setVerticalFOV(40.0);
//     cam->setAperture(0.3);
//     cam->setFocusDist((Vector3(8.0, 2.0, 2.0) - Vector3(0.0, 1.0, 0.0)).length());
//     result->setCamera(cam);

//     std::shared_ptr<Shape> sphereShape = std::make_shared<Sphere>();

//     std::shared_ptr<ShapeGroup> world = std::make_shared<ShapeGroup>();

//     std::shared_ptr<ShapeInstance> floorSphere = std::make_shared<ShapeInstance>();
//     floorSphere->setShape(sphereShape);
//     floorSphere->getTransform()->setLocationY(-1000.0);
//     floorSphere->getTransform()->setUniformScale(1000.0);
//     floorSphere->setMaterial(std::make_shared<Lambert>(Color(0.5, 0.5, 0.5)));

//     world->addShape(floorSphere);

//     for(int a = -11; a < 11; a++) {
//         for(int b = -11; b < 11; b++) {
//             float chooseMat = Plutonium::getRandomNumber();
//             Vector3 center(a + 0.9 * Plutonium::getRandomNumber(), 0.3, b + 0.9 * Plutonium::getRandomNumber());
//             if((center - Vector3(4.0, 0.2, 0.0)).length() > 0.9) {
//                 std::shared_ptr<ShapeInstance> currentSphere = std::make_shared<ShapeInstance>();
//                 currentSphere->setShape(sphereShape);
//                 currentSphere->getTransform()->setLocationX(center.x());
//                 currentSphere->getTransform()->setLocationY(center.y());
//                 currentSphere->getTransform()->setLocationZ(center.z());
//                 currentSphere->getTransform()->setRotationX(360.0 * Plutonium::getRandomNumber());
//                 currentSphere->getTransform()->setRotationY(360.0 * Plutonium::getRandomNumber());
//                 currentSphere->getTransform()->setRotationZ(360.0 * Plutonium::getRandomNumber());
//                 currentSphere->getTransform()->setScaleX(0.1 + 0.2 * Plutonium::getRandomNumber());
//                 currentSphere->getTransform()->setScaleY(0.1 + 0.2 * Plutonium::getRandomNumber());
//                 currentSphere->getTransform()->setScaleZ(0.1 + 0.2 * Plutonium::getRandomNumber());
//                 if(chooseMat < 0.8) {
//                     currentSphere->setMaterial(std::make_shared<Lambert>(Color(Plutonium::getRandomNumber() * Plutonium::getRandomNumber(), Plutonium::getRandomNumber() * Plutonium::getRandomNumber(), Plutonium::getRandomNumber() * Plutonium::getRandomNumber())));
//                 }
//                 else if(chooseMat < 0.95) {
//                     currentSphere->setMaterial(std::make_shared<Metal>(Color(0.5 * (1.0 + Plutonium::getRandomNumber()), 0.5 * (1.0 + Plutonium::getRandomNumber()), 0.5 * (1.0 + Plutonium::getRandomNumber())), 0.5 * Plutonium::getRandomNumber()));
//                 }
//                 else {
//                     currentSphere->setMaterial(std::make_shared<Dielectric>(1.5));
//                 }

//                 world->addShape(currentSphere);
//             }
//         }
//     }

//     std::shared_ptr<ShapeInstance> bigSphere1 = std::make_shared<ShapeInstance>();
//     bigSphere1->setShape(sphereShape);
//     bigSphere1->getTransform()->setLocationY(1.0);
//     bigSphere1->setMaterial(std::make_shared<Dielectric>(1.5));
//     world->addShape(bigSphere1);

//     std::shared_ptr<ShapeInstance> bigSphere2 = std::make_shared<ShapeInstance>();
//     bigSphere2->setShape(sphereShape);
//     bigSphere2->getTransform()->setLocationX(-4.0);
//     bigSphere2->getTransform()->setLocationY(1.0);
//     bigSphere2->setMaterial(std::make_shared<Lambert>(Color(0.4, 0.2, 0.1)));
//     world->addShape(bigSphere2);

//     std::shared_ptr<ShapeInstance> bigSphere3 = std::make_shared<ShapeInstance>();
//     bigSphere3->setShape(sphereShape);
//     bigSphere3->getTransform()->setLocationX(4.0);
//     bigSphere3->getTransform()->setLocationY(1.0);
//     bigSphere3->setMaterial(std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0));
//     world->addShape(bigSphere3);

//     result->setShapeGroup(world);

//     return result;
// }


// std::shared_ptr<Scene> createScene() {
//     std::shared_ptr<Scene> result = std::make_shared<Scene>();

//     std::shared_ptr<Camera> cam = std::make_shared<Camera>();
//     cam->setLookFrom(Vector3(0.0, 0.0, 3.0));
//     cam->setLookAt(Vector3(0.0, 0.0, 0.0));
//     result->setCamera(cam);


//     std::shared_ptr<Shape> sphereShape = std::make_shared<Sphere>();

//     std::shared_ptr<ShapeInstance> sphere1 = std::make_shared<ShapeInstance>();
//     sphere1->setShape(sphereShape);
//     sphere1->getTransform()->setLocationX(-2.2);
//     sphere1->getTransform()->setLocationZ(1.0);
//     sphere1->getTransform()->setUniformScale(0.8);
//     sphere1->setMaterial(std::make_shared<Lambert>(Color(0.0, 1.0, 0.0)));

//     std::shared_ptr<ShapeInstance> ellipsoid1 = std::make_shared<ShapeInstance>();
//     ellipsoid1->setShape(sphereShape);
//     ellipsoid1->getTransform()->setLocationX(2.0);
//     ellipsoid1->getTransform()->setRotationZ(45.0);
//     ellipsoid1->getTransform()->setScaleX(2.0);
//     ellipsoid1->setMaterial(std::make_shared<Metal>(Color(0.8, 0.8, 0.8), 0.1));

//     std::shared_ptr<ShapeGroup> world = std::make_shared<ShapeGroup>();
//     world->addShape(sphere1);
//     world->addShape(ellipsoid1);
//     result->setShapeGroup(world);

//     return result;
// }


// std::shared_ptr<Scene> createScene() {
//     std::shared_ptr<Scene> result = std::make_shared<Scene>();

//     std::shared_ptr<Camera> cam = std::make_shared<Camera>();
//     cam->setLookFrom(Vector3(0.0, 1.0, 3.0));
//     cam->setLookAt(Vector3(0.0, 0.0, 0.0));
//     result->setCamera(cam);

//     std::shared_ptr<Triangle> tri1 = std::make_shared<Triangle>(Vector3(0.0, 0.5, 0.0), Vector3(-0.3, 0.4, 1.0), Vector3(-0.6, -0.6, 1.2));
//     std::shared_ptr<Triangle> tri2 = std::make_shared<Triangle>(Vector3(0.0, 0.5, 0.0), Vector3(0.5, -0.5, 0.2), Vector3(0.4, 0.6, 0.3));
//     std::shared_ptr<Rectangle> rect = std::make_shared<Rectangle>();

//     std::shared_ptr<ShapeInstance> triInst1 = std::make_shared<ShapeInstance>();
//     triInst1->setShape(tri1);
//     triInst1->setMaterial(std::make_shared<Lambert>(Color(1.0, 0.0, 0.0)));
    
//     std::shared_ptr<ShapeInstance> triInst2 = std::make_shared<ShapeInstance>();
//     triInst2->setShape(tri2);
//     triInst2->setMaterial(std::make_shared<Metal>(Color(0.8, 0.8, 0.8), 0.1));
    
//     std::shared_ptr<ShapeInstance> triInst3 = std::make_shared<ShapeInstance>();
//     triInst3->setShape(tri2);
//     triInst3->getTransform()->setLocationX(1.0);
//     triInst3->setMaterial(std::make_shared<Lambert>(Color(0.0, 0.0, 1.0)));

//     std::shared_ptr<ShapeInstance> rectInst = std::make_shared<ShapeInstance>();
//     rectInst->setShape(rect);
//     rectInst->getTransform()->setLocationY(-0.65);
//     rectInst->getTransform()->setUniformScale(2.0);
//     rectInst->getTransform()->setRotationY(-20.0);
//     rectInst->setMaterial(std::make_shared<Lambert>(Color(1.0, 1.0, 0.0)));

//     std::shared_ptr<ShapeGroup> world = std::make_shared<ShapeGroup>();
//     world->addShape(triInst1);
//     world->addShape(triInst2);
//     world->addShape(triInst3);
//     world->addShape(rectInst);

//     result->setShapeGroup(world);

//     return result;
// }


// std::shared_ptr<Scene> createScene() {
//     std::shared_ptr<Scene> result = std::make_shared<Scene>();

//     std::shared_ptr<Camera> cam = std::make_shared<Camera>();
//     cam->setResolution(400, 300);
//     cam->setLookFrom(Vector3(2.0, 1.0, 4.0));
//     cam->setLookAt(Vector3(0.0, 0.0, 0.0));
//     result->setCamera(cam);

//     std::shared_ptr<Shape> cube = std::make_shared<MeshRef>(std::make_shared<IndexedTriangleMesh>(MeshType::Cube));
//     std::shared_ptr<Shape> sphere = std::make_shared<Sphere>();
//     std::shared_ptr<Shape> rect = std::make_shared<Rectangle>();

//     std::shared_ptr<ShapeInstance> cubeInst = std::make_shared<ShapeInstance>();
//     cubeInst->setShape(cube);
//     cubeInst->getTransform()->setScaleZ(0.1);
//     cubeInst->setMaterial(std::make_shared<Dielectric>(1.5));

//     std::shared_ptr<ShapeInstance> sphereInst1 = std::make_shared<ShapeInstance>();
//     sphereInst1->setShape(sphere);
//     sphereInst1->getTransform()->setLocationX(1.0);
//     sphereInst1->getTransform()->setLocationY(-1.0);
//     sphereInst1->getTransform()->setLocationZ(-2.0);
//     sphereInst1->getTransform()->setUniformScale(0.4);
//     sphereInst1->setMaterial(std::make_shared<Lambert>(Color(0.2, 0.2, 0.2)));

//     std::shared_ptr<ShapeInstance> sphereInst2 = std::make_shared<ShapeInstance>();
//     sphereInst2->setShape(sphere);
//     sphereInst2->getTransform()->setLocationX(-1.0);
//     sphereInst2->getTransform()->setLocationY(1.0);
//     sphereInst2->getTransform()->setLocationZ(-2.0);
//     sphereInst2->getTransform()->setUniformScale(0.4);
//     sphereInst2->setMaterial(std::make_shared<Lambert>(Color(0.2, 0.2, 1.0)));

//     std::shared_ptr<ShapeInstance> sphereInst3 = std::make_shared<ShapeInstance>();
//     sphereInst3->setShape(sphere);
//     sphereInst3->getTransform()->setLocationX(1.0);
//     sphereInst3->getTransform()->setLocationY(1.0);
//     sphereInst3->getTransform()->setLocationZ(-2.0);
//     sphereInst3->getTransform()->setUniformScale(0.4);
//     sphereInst3->setMaterial(std::make_shared<Dielectric>(1.5));

//     std::shared_ptr<ShapeInstance> sphereInst4 = std::make_shared<ShapeInstance>();
//     sphereInst4->setShape(sphere);
//     sphereInst4->getTransform()->setLocationX(-1.0);
//     sphereInst4->getTransform()->setLocationY(-1.0);
//     sphereInst4->getTransform()->setLocationZ(-2.0);
//     sphereInst4->getTransform()->setUniformScale(0.4);
//     sphereInst4->setMaterial(std::make_shared<Metal>(Color(0.8, 0.8, 1.0), 0.3));

//     std::shared_ptr<ShapeInstance> rectInst = std::make_shared<ShapeInstance>();
//     rectInst->setShape(rect);
//     rectInst->getTransform()->setLocationY(-1.5);
//     rectInst->getTransform()->setUniformScale(10.0);
//     rectInst->setMaterial(std::make_shared<Lambert>(Color(0.5, 0.5, 0.5)));

//     std::shared_ptr<ShapeGroup> world = std::make_shared<ShapeGroup>();
//     world->addShape(cubeInst);
//     world->addShape(sphereInst1);
//     world->addShape(sphereInst2);
//     world->addShape(sphereInst3);
//     world->addShape(sphereInst4);
//     world->addShape(rectInst);

//     result->setShapeGroup(world);

//     return result;
// }



std::shared_ptr<Scene> createScene() {
    std::shared_ptr<Scene> result = std::make_shared<Scene>();

    std::shared_ptr<Camera> cam = std::make_shared<Camera>();
    cam->setResolution(200, 300);
    cam->setLookFrom(Vector3(7.0, 10.0, 7.0));
    cam->setLookAt(Vector3(0.0, 5.0, 0.0));
    cam->setVerticalFOV(60.0);
    result->setCamera(cam);

    std::shared_ptr<Shape> cube1 = std::make_shared<MeshRef>(std::make_shared<IndexedTriangleMesh>(MeshType::Cube));
    std::shared_ptr<Shape> cube2 = std::make_shared<MeshRef>(std::make_shared<TriangleFanMesh>(MeshType::Cube));
    std::shared_ptr<Shape> cube3 = std::make_shared<MeshRef>(std::make_shared<TriangleStripMesh>(MeshType::Cube));
    std::shared_ptr<Shape> cube4 = std::make_shared<MeshRef>(std::make_shared<HalfEdgeMesh>(MeshType::Cube));
    std::shared_ptr<Shape> cube5 = std::make_shared<MeshRef>(std::make_shared<TriangleFanMesh>("../assets/Cube/Cube.obj"));

    std::shared_ptr<ShapeInstance> cubeInst1 = std::make_shared<ShapeInstance>();
    cubeInst1->setShape(cube1);
    cubeInst1->setMaterial(std::make_shared<Lambert>(Color(0.5, 0.0, 0.0)));

    std::shared_ptr<ShapeInstance> cubeInst2 = std::make_shared<ShapeInstance>();
    cubeInst2->setShape(cube2);
    cubeInst2->getTransform()->setLocationY(2.0);
    cubeInst2->getTransform()->setRotationY(20.0);
    cubeInst2->setMaterial(std::make_shared<Lambert>(Color(0.0, 0.5, 0.0)));

    std::shared_ptr<ShapeInstance> cubeInst3 = std::make_shared<ShapeInstance>();
    cubeInst3->setShape(cube2);
    cubeInst3->getTransform()->setLocationY(4.0);
    cubeInst3->getTransform()->setRotationY(40.0);
    cubeInst3->setMaterial(std::make_shared<Lambert>(Color(0.0, 0.0, 0.5)));

    std::shared_ptr<ShapeInstance> cubeInst4 = std::make_shared<ShapeInstance>();
    cubeInst4->setShape(cube2);
    cubeInst4->getTransform()->setLocationY(6.0);
    cubeInst4->getTransform()->setRotationY(60.0);
    cubeInst4->setMaterial(std::make_shared<Lambert>(Color(0.5, 0.0, 0.5)));

    std::shared_ptr<ShapeInstance> cubeInst5 = std::make_shared<ShapeInstance>();
    cubeInst5->setShape(cube2);
    cubeInst5->getTransform()->setLocationY(8.0);
    cubeInst5->getTransform()->setRotationY(80.0);
    cubeInst5->setMaterial(std::make_shared<Lambert>(Color(0.0, 0.5, 0.5)));

    std::shared_ptr<ShapeGroup> world = std::make_shared<ShapeGroup>();
    world->addShape(cubeInst1);
    world->addShape(cubeInst2);
    world->addShape(cubeInst3);
    world->addShape(cubeInst4);
    world->addShape(cubeInst5);

    result->setShapeGroup(world);

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