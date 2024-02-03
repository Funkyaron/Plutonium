

#include "ProbabilityDensityFunction.h"



float MixtureProbabilityDensityFunction::value(const Vector3& direction) const {
    return 0.5 * pdf1->value(direction) + 0.5 * pdf2->value(direction);
}

Vector3 MixtureProbabilityDensityFunction::generate() const {
    if(Plutonium::getRandomNumber() < 0.5) {
        return pdf1->generate();
    }
    else {
        return pdf2->generate();
    }
}