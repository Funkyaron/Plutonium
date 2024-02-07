


#ifndef PLUTONIUM_PROBABILITYDENSITYFUNCTION_H
#define PLUTONIUM_PROBABILITYDENSITYFUNCTION_H


#include "Vector3.h"
#include "OrthoNormalBasis.h"
#include "Shape.h"
#include "BoundingBox.h"

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


class BoxProbabilityDensityFunction : public ProbabilityDensityFunction {
public:

    BoxProbabilityDensityFunction(const BoundingBox& bbox_) : bbox(bbox_) {}
    BoxProbabilityDensityFunction(const BoundingBox& bbox_, const Vector3& origin_) : bbox(bbox_), origin(origin_) {}

    void setOrigin(const Vector3& origin_);

    virtual float value(const Vector3& direction) const override;
    virtual Vector3 generate() const override;

private:

    float xminValue(const Vector3& origin, const Vector3& direction, float t0, float t1) const;
    float xmaxValue(const Vector3& origin, const Vector3& direction, float t0, float t1) const;
    float yminValue(const Vector3& origin, const Vector3& direction, float t0, float t1) const;
    float ymaxValue(const Vector3& origin, const Vector3& direction, float t0, float t1) const;
    float zminValue(const Vector3& origin, const Vector3& direction, float t0, float t1) const;
    float zmaxValue(const Vector3& origin, const Vector3& direction, float t0, float t1) const;

    Vector3 origin;
    BoundingBox bbox;

};


class BoxListProbabilityDensityFunction : public ProbabilityDensityFunction {
public:

    BoxListProbabilityDensityFunction(const std::vector<BoundingBox>& boxes_, const Vector3& origin_) : boxes(boxes_), origin(origin_) {}

    virtual float value(const Vector3& direction) const override;
    virtual Vector3 generate() const override;

private:

    Vector3 origin;
    std::vector<BoundingBox> boxes;

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