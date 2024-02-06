



#include "Material.h"
#include "Ray.h"
#include "Color.h"
#include "Vector3.h"
#include "Utility.h"




bool Metal::scatter(const Ray& rIn, const HitRecord& hrec, ScatterRecord& srec) const {
    Vector3 reflected = reflect(unitVector(rIn.getDirection()), hrec.normal);
    srec.specularRay = Ray(hrec.p, reflected + roughness * Plutonium::randomInUnitSphere());
    srec.attenuation = albedo;
    srec.isSpecular = true;
    srec.pdf = nullptr;
    return true;
}

float Metal::scatteringpdf(const Ray& rIn, const HitRecord& rec, const Ray& scattered) const {
    return 0.0;
}
