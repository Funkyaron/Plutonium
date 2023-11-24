


#ifndef PLUTONIUM_RENDERER_H
#define PLUTONIUM_RENDERER_H


#include <memory>


class PixelBuffer;
class Scene;


namespace Plutonium {
    void renderScene(std::shared_ptr<Scene> scene, PixelBuffer& buf);
}




#endif