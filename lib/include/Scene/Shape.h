


#ifndef PLUTONIUM_SHAPE_H
#define PLUTONIUM_SHAPE_H


#include <memory>
#include <vector>

#include "Vector3.h"

class Ray;
class Material;
class Transform;


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


class Geometry : public Shape {
public:

private:

};


class GeometryInstance : public Shape {
public:

    GeometryInstance();
    GeometryInstance(std::shared_ptr<Geometry> geometry_, std::shared_ptr<Transform> transform_, std::shared_ptr<Material> material_);

    virtual bool hit(Ray r, float t0, float t1, HitRecord& rec) const override;

    void setGeometry(std::shared_ptr<Geometry> geometry_);
    std::shared_ptr<Geometry> getGeometry() const;

    void setTransform(std::shared_ptr<Transform> transform_);
    std::shared_ptr<Transform> getTransform() const;

    void setMaterial(std::shared_ptr<Material> material_);
    std::shared_ptr<Material> getMaterial() const;

private:

    std::shared_ptr<Geometry> geometry;
    std::shared_ptr<Transform> transform;
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


class Sphere : public Geometry {
public:

    Sphere() {}

    virtual bool hit(Ray r, float t0, float t1, HitRecord& rec) const override;

private:

};




#endif