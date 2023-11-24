


#include "Shape.h"
#include "Ray.h"



void ShapeGroup::addShape(std::shared_ptr<Shape> newShape) {
    shapes.push_back(newShape);
}

bool ShapeGroup::hit(Ray r, float t0, float t1, HitRecord& rec) const {
    HitRecord tempRec;
    bool hitAnything = false;
    double closestSoFar = t1;
    for(auto& shape : shapes) {
        if(shape->hit(r, t0, closestSoFar, tempRec)) {
            hitAnything = true;
            closestSoFar = tempRec.t;
            rec = tempRec;
        }
    }
    return hitAnything;
}