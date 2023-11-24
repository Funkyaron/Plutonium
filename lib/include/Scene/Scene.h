


#ifndef PLUTONIUM_SCENE_H
#define PLUTONIUM_SCENE_H


#include <memory>

class Camera;
class Shape;


class Scene {
public:

    void setCamera(std::shared_ptr<Camera> newCam);
    std::shared_ptr<Camera> getCamera();
    
    void setWorldShape(std::shared_ptr<Shape> newWorld);
    std::shared_ptr<Shape> getWorldShape();

private:

    std::shared_ptr<Camera> cam;
    std::shared_ptr<Shape> world;

};






#endif