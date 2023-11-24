


#ifndef PLUTONIUM_SCENE_H
#define PLUTONIUM_SCENE_H


#include <memory>

class Camera;


class Scene {
public:

    void setCamera(std::shared_ptr<Camera> newCam);
    std::shared_ptr<Camera> getCamera();

private:

    std::shared_ptr<Camera> cam;

};






#endif