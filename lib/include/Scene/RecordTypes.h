
#ifndef PLUTONIUM_RECORDTYPES_H
#define PLUTONIUM_RECORDTYPES_H


#include "Vector3.h"
#include "Ray.h"
#include "Color.h"

#include <memory>

class Material;
class ProbabilityDensityFunction;


typedef struct {
    float t;
    Vector3 p;
    Vector3 normal;
    std::shared_ptr<Material> material;
} HitRecord;


typedef struct {
    Ray specularRay;
    bool isSpecular;
    Color attenuation;
    std::shared_ptr<ProbabilityDensityFunction> pdf;
} ScatterRecord;


#endif