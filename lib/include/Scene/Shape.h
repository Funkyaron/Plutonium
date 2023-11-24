


#ifndef PLUTONIUM_SHAPE_H
#define PLUTONIUM_SHAPE_H


#include <memory>
#include <vector>

#include "Vector3.h"

class Ray;



typedef struct {
    float t;
    Vector3 p;
    Vector3 normal;
} HitRecord;


class Shape {
public:

    virtual bool hit(Ray r, float t0, float t1, HitRecord& rec) const = 0;

private:

};


class Sphere : public Shape {
public:

    Sphere(Vector3 center_, float radius_) : center(center_), radius(radius_) {}

    virtual bool hit(Ray r, float t0, float t1, HitRecord& rec) const override;

private:

    Vector3 center;
    float radius;

};



class ShapeGroup : public Shape {
public:

    ShapeGroup() : shapes({}) {}

    void addShape(std::shared_ptr<Shape> newShape);

    virtual bool hit(Ray r, float t0, float t1, HitRecord& rec) const override;

private:

    std::vector<std::shared_ptr<Shape> > shapes;

};




#endif