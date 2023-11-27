


#ifndef PLUTONIUM_SHAPE_H
#define PLUTONIUM_SHAPE_H


#include <memory>
#include <vector>

#include "Vector3.h"
#include "Matrix4.h"

class Ray;
class Material;


typedef struct {
    float t;
    Vector3 p;
    Vector3 normal;
    std::shared_ptr<Material> material;
} HitRecord;


class Shape {
public:

    virtual bool hit(Ray r, float t0, float t1, HitRecord& rec) const = 0;

private:

};


class Sphere : public Shape {
public:

    Sphere(const Vector3& center_, float radius_, std::shared_ptr<Material> material_) : center(center_), radius(radius_), material(material_) {}

    virtual bool hit(Ray r, float t0, float t1, HitRecord& rec) const override;

private:

    Vector3 center;
    float radius;

    std::shared_ptr<Material> material;

};



class ShapeGroup : public Shape {
public:

    ShapeGroup() : shapes({}) {}

    void addShape(std::shared_ptr<Shape> newShape);

    virtual bool hit(Ray r, float t0, float t1, HitRecord& rec) const override;

private:

    std::vector<std::shared_ptr<Shape> > shapes;

};


class SphereInstance : public Shape {
public:

    SphereInstance();

    virtual bool hit(Ray r, float t0, float t1, HitRecord& rec) const override;

private:

    std::shared_ptr<Sphere> mSphere;
    Matrix4 transformMatrix;

};




#endif