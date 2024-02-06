


#ifndef PLUTONIUM_PROBABILITYDENSITYFUNCTION_H
#define PLUTONIUM_PROBABILITYDENSITYFUNCTION_H


#include "Vector3.h"
#include "OrthoNormalBasis.h"
#include "Shape.h"

#include <memory>


class ProbabilityDensityFunction {
public:

    virtual float value(const Vector3& direction) const = 0;
    virtual Vector3 generate() const = 0;

private:

};


class CosineProbabilityDensityFunction : public ProbabilityDensityFunction {
public:

    CosineProbabilityDensityFunction(const Vector3& w);

    virtual float value(const Vector3& direction) const override;
    virtual Vector3 generate() const override;

private:

    OrthoNormalBasis uvw;

};


class ShapeProbabilityDensityFunction : public ProbabilityDensityFunction {
public:

    ShapeProbabilityDensityFunction(std::shared_ptr<Shape> shapePtr_, const Vector3& origin_) : shapePtr(shapePtr_), origin(origin_) {}

    virtual float value(const Vector3& direction) const override;
    virtual Vector3 generate() const override;

private:

    Vector3 origin;
    std::shared_ptr<Shape> shapePtr;

};


class MixtureProbabilityDensityFunction : public ProbabilityDensityFunction {
public:

    MixtureProbabilityDensityFunction(std::shared_ptr<ProbabilityDensityFunction> pdf1_, std::shared_ptr<ProbabilityDensityFunction> pdf2_) : pdf1(pdf1_), pdf2(pdf2_) {}

    virtual float value(const Vector3& direction) const override;
    virtual Vector3 generate() const override;

private:

    std::shared_ptr<ProbabilityDensityFunction> pdf1;
    std::shared_ptr<ProbabilityDensityFunction> pdf2;

};




#endif