



#include "Scene.h"
#include "RendererCamera.h"



void Scene::setCamera(std::shared_ptr<RendererCamera> newCam) {
    cam = newCam;
}

std::shared_ptr<RendererCamera> Scene::getCamera() {
    return cam;
}

void Scene::setShapeGroup(std::shared_ptr<ShapeGroup> group) {
    shapeGroup = group;
}

std::shared_ptr<ShapeGroup> Scene::getShapeGroup() {
    return shapeGroup;
}