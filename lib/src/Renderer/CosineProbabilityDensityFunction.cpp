

#include "ProbabilityDensityFunction.h"
#include "Utility.h"

#include <numbers>


CosineProbabilityDensityFunction::CosineProbabilityDensityFunction(const Vector3& w) {
    uvw.buildFromW(w);
}

float CosineProbabilityDensityFunction::value(const Vector3& direction) const {
    float cosine = dot(unitVector(direction), uvw.w());
    if(cosine > 0.0) {
        return cosine / std::numbers::pi;
    }
    else {
        return 0.0;
    }
}

Vector3 CosineProbabilityDensityFunction::generate() const {
    return uvw.local(Plutonium::randomCosineDirection());
}