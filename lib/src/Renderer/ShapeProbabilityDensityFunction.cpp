




#include "ProbabilityDensityFunction.h"


float ShapeProbabilityDensityFunction::value(const Vector3& direction) const {
    return shapePtr->pdfValue(origin, direction);
}

Vector3 ShapeProbabilityDensityFunction::generate() const {
    return shapePtr->random(origin);
}