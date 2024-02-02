



// #include "Material.h"
// #include "Ray.h"
// #include "Color.h"
// #include "Vector3.h"
// #include "Utility.h"




// bool Metal::scatter(const Ray& rIn, const HitRecord& rec, Color& attenuation, Ray& scattered) const {
//     Vector3 reflected = reflect(unitVector(rIn.getDirection()), rec.normal);
//     scattered = Ray(rec.p, reflected + roughness * Plutonium::randomInUnitSphere());
//     attenuation = albedo;
//     return dot(reflected, rec.normal) > 0;
// }
