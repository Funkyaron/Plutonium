


#include <memory>
#include <limits>

#include "PixelBuffer.h"
#include "Camera.h"
#include "Color.h"
#include "Ray.h"
#include "Scene.h"
#include "Shape.h"


Color shadeRay(Ray r, std::shared_ptr<Scene> scene) {
    HitRecord rec;
    if(scene->getWorldShape()->hit(r, 0.001, std::numeric_limits<float>::max(), rec)) {
        return rec.normal.convertToColor();
    }
    else {
        Vector3 unitDirection = unitVector(r.getDirection());
        float t = 0.5 * unitDirection.y() + 1.0;
        return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
    }
}


namespace Plutonium {
    void renderScene(std::shared_ptr<Scene> scene, PixelBuffer& buf) {
        auto cam = scene->getCamera();
        buf.init(cam->getPixelWidth(), cam->getPixelHeight());

        int nsamples = 100;

        buf.forEach([&](int x, int y, Color& currentPixel) {
            Color col(0.0, 0.0, 0.0);
            for(int s = 0; s < nsamples; s++) {
                Ray r = cam->getRayForPixel(x, y);
                col += shadeRay(r, scene);
            }
            currentPixel = col / float(nsamples);
        });
    }
}