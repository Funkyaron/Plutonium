


#include "Shape.h"
#include "Ray.h"


#include <limits>



void ShapeGroup::addShape(std::shared_ptr<Shape> newShape) {
    shapes.push_back(newShape);
}

std::vector<std::shared_ptr<Shape> >& ShapeGroup::getShapes() {
    return shapes;
}

bool ShapeGroup::hit(Ray r, float t0, float t1, HitRecord& rec) const {
    HitRecord tempRec;
    bool hitAnything = false;
    float closestSoFar = t1;
    for(auto& shape : shapes) {
        if(shape->hit(r, t0, closestSoFar, tempRec)) {
            hitAnything = true;
            closestSoFar = tempRec.t;
            rec = tempRec;
        }
    }
    return hitAnything;
}


BoundingBox ShapeGroup::createBoundingBox() {
    float xmin = std::numeric_limits<float>::max();
    float xmax = std::numeric_limits<float>::lowest();
    float ymin = std::numeric_limits<float>::max();
    float ymax = std::numeric_limits<float>::lowest();
    float zmin = std::numeric_limits<float>::max();
    float zmax = std::numeric_limits<float>::lowest();

    for(auto &shape : shapes) {
        BoundingBox currentBBox = shape->createBoundingBox();
        if(currentBBox.getxmin() < xmin) {
            xmin = currentBBox.getxmin();
        }
        if(currentBBox.getxmax() > xmax) {
            xmax = currentBBox.getxmax();
        }
        if(currentBBox.getymin() < ymin) {
            ymin = currentBBox.getymin();
        }
        if(currentBBox.getymax() > ymax) {
            ymax = currentBBox.getymax();
        }
        if(currentBBox.getzmin() < zmin) {
            zmin = currentBBox.getzmin();
        }
        if(currentBBox.getzmax() > zmax) {
            zmax = currentBBox.getzmax();
        }
    }

    return BoundingBox(xmin, xmax, ymin, ymax, zmin, zmax);
}


Vector4 ShapeGroup::getCenter() {
    Vector4 result(0.0, 0.0, 0.0, 0.0);
    for(auto& shape : shapes) {
        result += shape->getCenter();
    }
    return result / float(shapes.size());
}


std::shared_ptr<Shape> ShapeGroup::buildBVH(int axis) {
    return BVHNode::create(shapes, axis);
}