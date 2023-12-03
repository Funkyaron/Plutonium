


#include <memory>
#include <limits>
#include <chrono>
#include <iostream>

#include "PixelBuffer.h"
#include "Camera.h"
#include "Color.h"
#include "Ray.h"
#include "Scene.h"
#include "Shape.h"
#include "Material.h"


Color shadeRay(Ray r, std::shared_ptr<BVHNode> bvhRoot, int depth) {
    HitRecord rec;
    if(bvhRoot->hit(r, 0.001, std::numeric_limits<float>::max(), rec)) {
        Ray scattered;
        Color attenuation;
        if(depth < 50 && rec.material->scatter(r, rec, attenuation, scattered)) {
            return attenuation * shadeRay(scattered, bvhRoot, depth + 1);
        }
        else {
            return Color(0.0, 0.0, 0.0);
        }
    }
    else {
        Vector3 unitDirection = unitVector(r.getDirection());
        float t = 0.5 * unitDirection.y() + 1.0;
        return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
    }
}


namespace Plutonium {
    void renderScene(std::shared_ptr<Scene> scene, PixelBuffer& buf) {

        auto start = std::chrono::high_resolution_clock::now();

        auto cam = scene->getCamera();
        buf.init(cam->getPixelWidth(), cam->getPixelHeight());

        std::shared_ptr<BVHNode> bvhRoot = BVHNode::create(scene->getShapeGroup()->getShapes(), 0);

        int nsamples = 10;

        buf.forEach([&](int x, int y, Color& currentPixel) {
            Color col(0.0, 0.0, 0.0);
            for(int s = 0; s < nsamples; s++) {
                Ray r = cam->getRayForPixel(x, y);
                col += shadeRay(r, bvhRoot, 0);
            }
            currentPixel = col / float(nsamples);
        });

        auto end = std::chrono::high_resolution_clock::now();

        const std::chrono::duration<double, std::ratio<1, 1>> timeSeconds = end - start;
        const std::chrono::duration<double, std::ratio<60, 1>> timeMinutes = end - start;

        // auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
        std::cout << "Render time: " << timeSeconds << " or " << timeMinutes << "\n";
    }
}