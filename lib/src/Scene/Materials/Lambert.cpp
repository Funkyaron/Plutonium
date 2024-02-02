




#include "Material.h"
#include "Utility.h"
#include "Ray.h"
#include "OrthoNormalBasis.h"

#include <numbers>



bool Lambert::scatter(const Ray& rIn, const HitRecord& rec, Color& attenuation, Ray& scattered, float& pdf) const {
    OrthoNormalBasis uvw;
    uvw.buildFromW(rec.normal);
    Vector3 direction = uvw.local(Plutonium::randomCosineDirection());
    scattered = Ray(rec.p, direction);
    attenuation = albedo;
    pdf = dot(uvw.w(), unitVector(scattered.getDirection())) / std::numbers::pi;
    return true;
}

float Lambert::scattering_pdf(const Ray& rIn, const HitRecord& rec, const Ray& scattered) const {
    float cosine = dot(rec.normal, unitVector(scattered.getDirection()));
    if(cosine < 0.0) {
        cosine = 0.0;
    }
    return cosine / std::numbers::pi;
}
