


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
#include "ProbabilityDensityFunction.h"


Color shadeRay(Ray r, std::shared_ptr<Shape> bvhRoot, std::shared_ptr<Shape> lightShape, int depth) {
    HitRecord hrec;
    if(bvhRoot->hit(r, 0.001, std::numeric_limits<float>::max(), hrec)) {
        ScatterRecord srec;
        Color emitted = hrec.material->emit();
        if(depth < 50 && hrec.material->scatter(r, hrec, srec)) {
            if(srec.isSpecular) {
                return srec.attenuation * shadeRay(srec.specularRay, bvhRoot, lightShape, depth + 1);
            }
            else {
                auto lightpdf = std::make_shared<ShapeProbabilityDensityFunction>(lightShape, hrec.p);
                auto mixpdf = std::make_shared<MixtureProbabilityDensityFunction>(lightpdf, srec.pdf);
                Ray scattered(hrec.p, mixpdf->generate());
                float pdfValue = mixpdf->value(scattered.getDirection());
                return emitted + srec.attenuation * hrec.material->scatteringpdf(r, hrec, scattered) * shadeRay(scattered, bvhRoot, lightShape, depth + 1) / pdfValue;
            }
        }
        else {
            return emitted;
        }
    }
    else {
        return Color(0.0, 0.0, 0.0);
    }
}


namespace Plutonium {
    void renderScene(std::shared_ptr<Scene> scene, PixelBuffer& buf) {

        auto start = std::chrono::high_resolution_clock::now();

        auto cam = scene->getCamera();
        buf.init(cam->getPixelWidth(), cam->getPixelHeight());

        std::shared_ptr<Shape> bvhRoot = scene->getShapeGroup()->buildBVH(0);
        std::shared_ptr<Shape> lightShape = std::make_shared<xz_rect>(213, 343, 227, 332, 554, nullptr);

        int nsamples = 300;

        buf.forEachConcurrent([&](int x, int y, Color& currentPixel) {
            Color col(0.0, 0.0, 0.0);
            for(int s = 0; s < nsamples; s++) {
                Ray r = cam->getRayForPixel(x, y);
                col += shadeRay(r, bvhRoot, lightShape, 0);
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