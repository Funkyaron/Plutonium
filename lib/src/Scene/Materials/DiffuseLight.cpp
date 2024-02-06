

#include "Material.h"



bool DiffuseLight::scatter(const Ray& rIn, const HitRecord& hrec, ScatterRecord& srec) const {
    return false;
}

float DiffuseLight::scatteringpdf(const Ray& rIn, const HitRecord& rec, const Ray& scattered) const {
    return 0.0; 
}

Color DiffuseLight::emit() const {
    return emittedColor;
}