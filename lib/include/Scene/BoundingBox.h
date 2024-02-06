


#ifndef PLUTONIUM_BOUNDINGBOX_H
#define PLUTONIUM_BOUNDINGBOX_H


#include "RecordTypes.h"

class Ray;


class BoundingBox {
public:

    BoundingBox() {}
    BoundingBox(float xmin_, float xmax_, float ymin_, float ymax_, float zmin_, float zmax_);
    BoundingBox(const BoundingBox& bbox1, const BoundingBox& bbox2);

    bool hit(Ray r, float t0, float t1) const;
    // bool hit(Ray r, float t0, float t1, HitRecord hrec) const;

    float getxmin() const;
    float getxmax() const;
    float getymin() const;
    float getymax() const;
    float getzmin() const;
    float getzmax() const;

private:

    float xmin, xmax, ymin, ymax, zmin, zmax;

};





#endif