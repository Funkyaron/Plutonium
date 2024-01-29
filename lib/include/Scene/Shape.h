


#ifndef PLUTONIUM_SHAPE_H
#define PLUTONIUM_SHAPE_H


#include <memory>
#include <vector>

#include "Vector3.h"
#include "Vector4.h"
#include "BoundingBox.h"

class Ray;
class Material;
class Transform;
class Mesh;


typedef struct {
    float t;
    Vector3 p;
    Vector3 normal;
    std::shared_ptr<Material> material;
} HitRecord;


class Shape : public std::enable_shared_from_this<Shape> {
public:

    virtual bool hit(Ray r, float t0, float t1, HitRecord& rec) const = 0;
    virtual BoundingBox createBoundingBox() = 0;
    virtual Vector4 getCenter() = 0;

    virtual std::shared_ptr<Shape> buildBVH(int axis) { return shared_from_this(); }

private:

};


class BVHNode : public Shape {
public:

    static std::shared_ptr<BVHNode> create(std::vector<std::shared_ptr<Shape> > shapes, int axis);

    virtual bool hit(Ray r, float t0, float t1, HitRecord& rec) const override;
    virtual BoundingBox createBoundingBox() override;
    virtual Vector4 getCenter() override;

    void setLeft(std::shared_ptr<Shape> shape);
    void setRight(std::shared_ptr<Shape> shape);
    void setBBox(const BoundingBox& box);

private:

    std::shared_ptr<Shape> left;
    std::shared_ptr<Shape> right;
    BoundingBox bbox;

};


class ShapeInstance : public Shape {
public:

    ShapeInstance();
    ShapeInstance(std::shared_ptr<Shape> shape_, std::shared_ptr<Transform> transform_, std::shared_ptr<Material> material_);

    virtual bool hit(Ray r, float t0, float t1, HitRecord& rec) const override;
    virtual BoundingBox createBoundingBox() override;
    virtual Vector4 getCenter() override;

    virtual std::shared_ptr<Shape> buildBVH(int axis) override;

    void setShape(std::shared_ptr<Shape> shape_);
    std::shared_ptr<Shape> getShape() const;

    void setTransform(std::shared_ptr<Transform> transform_);
    std::shared_ptr<Transform> getTransform() const;

    void setMaterial(std::shared_ptr<Material> material_);
    std::shared_ptr<Material> getMaterial() const;

private:

    std::shared_ptr<Shape> shape;
    std::shared_ptr<Transform> transform;
    std::shared_ptr<Material> material;

};



class ShapeGroup : public Shape {
public:

    ShapeGroup() : shapes({}) {}

    void addShape(std::shared_ptr<Shape> newShape);
    std::vector<std::shared_ptr<Shape> >& getShapes();

    virtual bool hit(Ray r, float t0, float t1, HitRecord& rec) const override;
    virtual BoundingBox createBoundingBox() override;
    virtual Vector4 getCenter() override;

    virtual std::shared_ptr<Shape> buildBVH(int axis) override;

private:

    std::vector<std::shared_ptr<Shape> > shapes;

};


class Sphere : public Shape {
public:

    Sphere() {}

    virtual bool hit(Ray r, float t0, float t1, HitRecord& rec) const override;
    virtual BoundingBox createBoundingBox() override;
    virtual Vector4 getCenter() override;

private:

};


class Triangle : public Shape {
public:

    Triangle(const Vector3& p1_, const Vector3& p2_, const Vector3& p3_) : p1(Vector4::position(p1_)), p2(Vector4::position(p2_)), p3(Vector4::position(p3_)) {}
    Triangle(const Vector4& p1_, const Vector4& p2_, const Vector4& p3_) : p1(p1_), p2(p2_), p3(p3_) {}

    virtual bool hit(Ray r, float t0, float t1, HitRecord& rec) const override;
    virtual BoundingBox createBoundingBox() override;
    virtual Vector4 getCenter() override;

private:

    Vector4 p1, p2, p3;

};


class Rectangle : public Shape {
public:

    Rectangle() {}

    virtual bool hit(Ray r, float t0, float t1, HitRecord& rec) const override;
    virtual BoundingBox createBoundingBox() override;
    virtual Vector4 getCenter() override;

private:

};



class MeshRef : public Shape {
public:

    MeshRef(std::shared_ptr<Mesh> mesh_) : mesh(mesh_) {}

    virtual bool hit(Ray r, float t0, float t1, HitRecord& rec) const override;
    virtual BoundingBox createBoundingBox() override;
    virtual Vector4 getCenter() override;

    virtual std::shared_ptr<Shape> buildBVH(int axis) override;

private:

    std::shared_ptr<Mesh> mesh;

};




#endif