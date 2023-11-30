


#ifndef PLUTONIUM_SCENE_H
#define PLUTONIUM_SCENE_H


#include <memory>

class Camera;
class ShapeGroup;


class Scene {
public:

    void setCamera(std::shared_ptr<Camera> newCam);
    std::shared_ptr<Camera> getCamera();
    
    void setShapeGroup(std::shared_ptr<ShapeGroup> group);
    std::shared_ptr<ShapeGroup> getShapeGroup();

private:

    std::shared_ptr<Camera> cam;
    std::shared_ptr<ShapeGroup> shapeGroup;

};






#endif