

#include "Material.h"
#include "Ray.h"
#include "Utility.h"


bool Dielectric::scatter(const Ray& rIn, const HitRecord& hrec, ScatterRecord& srec) const {
    Vector3 outwardNormal;
    Vector3 reflected = reflect(rIn.getDirection(), hrec.normal);
    float ni_over_nt;

    Vector3 refracted;
    float reflectProb;
    float cosine;

    if(dot(rIn.getDirection(), hrec.normal) > 0) {
        outwardNormal = -hrec.normal;
        ni_over_nt = refractionIndex;
        cosine = refractionIndex * dot(rIn.getDirection(), hrec.normal) / rIn.getDirection().length();
    }
    else {
        outwardNormal = hrec.normal;
        ni_over_nt = 1.0 / refractionIndex;
        cosine = -dot(rIn.getDirection(), hrec.normal) / rIn.getDirection().length();
    }

    if(refract(rIn.getDirection(), outwardNormal, ni_over_nt, refracted)) {
        reflectProb = schlick(cosine, refractionIndex);
    }
    else {
        reflectProb = 1.0;
    }

    if(Plutonium::getRandomNumber() < reflectProb) {
        srec.specularRay = Ray(hrec.p, reflected);
    }
    else {
        srec.specularRay = Ray(hrec.p, refracted);
    }

    srec.isSpecular = true;
    srec.attenuation = Color(1.0, 1.0, 1.0);
    srec.pdf = nullptr;
    return true;
}

float Dielectric::scatteringpdf(const Ray& rIn, const HitRecord& rec, const Ray& scattered) const {
    return 0.0;
}

float Dielectric::schlick(float cosine, float refractionIndex) const {
    float r0 = (1 - refractionIndex) / (1 + refractionIndex);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}
