




#include "Material.h"
#include "Utility.h"
#include "Ray.h"
#include "OrthoNormalBasis.h"
#include "ProbabilityDensityFunction.h"

#include <numbers>



bool Lambert::scatter(const Ray& rIn, const HitRecord& hrec, ScatterRecord& srec) const {
    srec.isSpecular = false;
    srec.attenuation = albedo;
    srec.pdf = std::make_shared<CosineProbabilityDensityFunction>(hrec.normal);
    return true;
}

float Lambert::scatteringpdf(const Ray& rIn, const HitRecord& rec, const Ray& scattered) const {
    float cosine = dot(rec.normal, unitVector(scattered.getDirection()));
    if(cosine < 0.0) {
        cosine = 0.0;
    }
    return cosine / std::numbers::pi;
}
