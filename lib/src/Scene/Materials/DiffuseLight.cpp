

#include "Material.h"



bool DiffuseLight::scatter(const Ray& rIn, const HitRecord& rec, Color& attenuation, Ray& scattered, float& pdf) const {
    return false;
}

float DiffuseLight::scattering_pdf(const Ray& rIn, const HitRecord& rec, const Ray& scattered) const {
    return 0.0; 
}

Color DiffuseLight::emit() const {
    return emittedColor;
}