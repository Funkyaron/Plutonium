


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


Color shadeRay(Ray r, std::shared_ptr<Shape> bvhRoot, int depth) {
    HitRecord rec;
    if(bvhRoot->hit(r, 0.001, std::numeric_limits<float>::max(), rec)) {
        Ray scattered;
        Color attenuation;
        Color emitted = rec.material->emit();
        float pdf;
        if(depth < 50 && rec.material->scatter(r, rec, attenuation, scattered, pdf)) {
            std::shared_ptr<Shape> lightShape = std::make_shared<xz_rect>(213, 343, 227, 332, 554, nullptr);
            ShapeProbabilityDensityFunction lightpdf(lightShape, rec.p);
            CosineProbabilityDensityFunction cospdf(rec.normal);
            MixtureProbabilityDensityFunction mixpdf(&lightpdf, &cospdf);
            scattered = Ray(rec.p, mixpdf.generate());
            pdf = mixpdf.value(scattered.getDirection());
            return emitted + attenuation * rec.material->scattering_pdf(r, rec, scattered) * shadeRay(scattered, bvhRoot, depth + 1) / pdf;
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

        int nsamples = 1000;

        buf.forEachConcurrent([&](int x, int y, Color& currentPixel) {
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