

#include "Material.h"
#include "Ray.h"
#include "Utility.h"


bool Dielectric::scatter(const Ray& rIn, const HitRecord& rec, Color& attenuation, Ray& scattered) const {
    Vector3 outwardNormal;
    Vector3 reflected = reflect(rIn.getDirection(), rec.normal);
    float ni_over_nt;

    attenuation = Color(1.0, 1.0, 1.0);

    Vector3 refracted;
    float reflectProb;
    float cosine;

    if(dot(rIn.getDirection(), rec.normal) > 0) {
        outwardNormal = -rec.normal;
        ni_over_nt = refractionIndex;
        cosine = refractionIndex * dot(rIn.getDirection(), rec.normal) / rIn.getDirection().length();
    }
    else {
        outwardNormal = rec.normal;
        ni_over_nt = 1.0 / refractionIndex;
        cosine = -dot(rIn.getDirection(), rec.normal) / rIn.getDirection().length();
    }

    if(refract(rIn.getDirection(), outwardNormal, ni_over_nt, refracted)) {
        reflectProb = schlick(cosine, refractionIndex);
    }
    else {
        reflectProb = 1.0;
    }

    if(Plutonium::getRandomNumber() < reflectProb) {
        scattered = Ray(rec.p, reflected);
    }
    else {
        scattered = Ray(rec.p, refracted);
    }
    return true;
}

float Dielectric::schlick(float cosine, float refractionIndex) const {
    float r0 = (1 - refractionIndex) / (1 + refractionIndex);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}
