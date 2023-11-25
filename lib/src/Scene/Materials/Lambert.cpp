




#include "Material.h"
#include "Utility.h"
#include "Ray.h"



bool Lambert::scatter(const Ray& rIn, const HitRecord& rec, Color& attenuation, Ray& scattered) const {
    Vector3 target = rec.p + rec.normal + Plutonium::randomInUnitSphere();
    scattered = Ray(rec.p, target - rec.p);
    attenuation = albedo;
    return true;
}
