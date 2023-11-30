



#include "Scene.h"
#include "Camera.h"



void Scene::setCamera(std::shared_ptr<Camera> newCam) {
    cam = newCam;
}

std::shared_ptr<Camera> Scene::getCamera() {
    return cam;
}

void Scene::setShapeGroup(std::shared_ptr<ShapeGroup> group) {
    shapeGroup = group;
}

std::shared_ptr<ShapeGroup> Scene::getShapeGroup() {
    return shapeGroup;
}