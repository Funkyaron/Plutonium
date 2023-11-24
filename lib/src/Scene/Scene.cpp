



#include "Scene.h"
#include "Camera.h"



void Scene::setCamera(std::shared_ptr<Camera> newCam) {
    cam = newCam;
}

std::shared_ptr<Camera> Scene::getCamera() {
    return cam;
}

void Scene::setWorldShape(std::shared_ptr<Shape> newWorld) {
    world = newWorld;
}

std::shared_ptr<Shape> Scene::getWorldShape() {
    return world;
}