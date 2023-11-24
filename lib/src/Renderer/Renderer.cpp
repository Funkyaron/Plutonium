


#include <memory>

#include "PixelBuffer.h"
#include "Camera.h"
#include "Color.h"
#include "Ray.h"
#include "Scene.h"


Color shadeRay(Ray r) {
    Vector3 unitDirection = unitVector(r.getDirection());
    float t = 0.5 * unitDirection.y() + 1.0;
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}


namespace Plutonium {
    void renderScene(std::shared_ptr<Scene> scene, PixelBuffer& buf) {
        auto cam = scene->getCamera();
        buf.init(cam->getPixelWidth(), cam->getPixelHeight());

        buf.forEach([&](int x, int y, Color& currentPixel) {
            Ray r = cam->getRayForPixel(x, y);
            currentPixel = shadeRay(r);
        });
    }
}