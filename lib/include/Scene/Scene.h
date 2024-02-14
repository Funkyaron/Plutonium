


#ifndef PLUTONIUM_SCENE_H
#define PLUTONIUM_SCENE_H


#include <memory>

class RendererCamera;
class ShapeGroup;


class Scene {
public:

    void setCamera(std::shared_ptr<RendererCamera> newCam);
    std::shared_ptr<RendererCamera> getCamera();
    
    void setShapeGroup(std::shared_ptr<ShapeGroup> group);
    std::shared_ptr<ShapeGroup> getShapeGroup();

private:

    std::shared_ptr<RendererCamera> cam;
    std::shared_ptr<ShapeGroup> shapeGroup;

};






#endif