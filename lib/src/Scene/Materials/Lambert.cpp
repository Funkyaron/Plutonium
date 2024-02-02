




#include "Material.h"
#include "Utility.h"
#include "Ray.h"

#include <numbers>



bool Lambert::scatter(const Ray& rIn, const HitRecord& rec, Color& attenuation, Ray& scattered, float& pdf) const {
    Vector3 target = rec.p + rec.normal + Plutonium::randomInUnitSphere();
    scattered = Ray(rec.p, target - rec.p);
    attenuation = albedo;
    pdf = dot(rec.normal, unitVector(scattered.getDirection())) / std::numbers::pi;
    return true;
}

float Lambert::scattering_pdf(const Ray& rIn, const HitRecord& rec, const Ray& scattered) const {
    float cosine = dot(rec.normal, unitVector(scattered.getDirection()));
    if(cosine < 0.0) {
        cosine = 0.0;
    }
    return cosine / std::numbers::pi;
}
