

#include "Material.h"



bool DiffuseLight::scatter(const Ray& rIn, const HitRecord& rec, Color& attenuation, Ray& scattered) const {
    return false;
}

Color DiffuseLight::emit() const {
    return emittedColor;
}