




#include "Shape.h"
#include "BoundingBox.h"
#include "Ray.h"


#include <iostream>
#include <algorithm>






std::shared_ptr<BVHNode> BVHNode::create(std::vector<std::shared_ptr<Shape> > shapes, int axis, std::vector<BoundingBox>& importantBoxes, std::function<bool(std::shared_ptr<ShapeInstance>)> ruleset) {

    std::shared_ptr<BVHNode> result = std::make_shared<BVHNode>();

    int n = shapes.size();
    if(n == 1) {
        result->setLeft(shapes[0]->buildBVH((axis + 1) % 3, importantBoxes, ruleset));
        result->setRight(nullptr);
        result->setBBox(shapes[0]->createBoundingBox());
    }
    else if(n == 2) {
        result->setLeft(shapes[0]->buildBVH((axis + 1) % 3, importantBoxes, ruleset));
        result->setRight(shapes[1]->buildBVH((axis + 1) % 3, importantBoxes, ruleset));
        result->setBBox(BoundingBox(shapes[0]->createBoundingBox(), shapes[1]->createBoundingBox()));
    }
    else {
        // Sort shapes by the object center along axis
        std::sort(shapes.begin(), shapes.end(), [&](std::shared_ptr<Shape> a, std::shared_ptr<Shape> b) {
            if(axis == 0) {
                return a->getCenter().x() > b->getCenter().x();
            }
            else if(axis == 1) {
                return a->getCenter().y() > b->getCenter().y();
            }
            else {
                return a->getCenter().z() > b->getCenter().z();
            }
        });
        std::vector<std::shared_ptr<Shape> > leftShapes = std::vector<std::shared_ptr<Shape> >(shapes.begin(), shapes.begin() + (n / 2));
        std::vector<std::shared_ptr<Shape> > rightShapes = std::vector<std::shared_ptr<Shape> >(shapes.begin() + (n / 2), shapes.end());
        std::shared_ptr<BVHNode> leftBVHNode = BVHNode::create(leftShapes, (axis + 1) % 3, importantBoxes, ruleset);
        std::shared_ptr<BVHNode> rightBVHNode = BVHNode::create(rightShapes, (axis + 1) % 3, importantBoxes, ruleset);
        result->setLeft(leftBVHNode);
        result->setRight(rightBVHNode);
        result->setBBox(BoundingBox(leftBVHNode->createBoundingBox(), rightBVHNode->createBoundingBox()));
    }

    return result;
}

bool BVHNode::hit(Ray r, float t0, float t1, HitRecord& rec) const {

    if(bbox.hit(r, t0, t1) == false) {
        return false;
    }

    HitRecord lrec, rrec;
    bool leftHit = (left != nullptr) && left->hit(r, t0, t1, lrec);
    bool rightHit = (right != nullptr) && right->hit(r, t0, t1, rrec);

    if(leftHit && rightHit) {
        if(lrec.t < rrec.t) {
            rec = lrec;
        }
        else {
            rec = rrec;
        }
        return true;
    }
    else if(leftHit) {
        rec = lrec;
        return true;
    }
    else if(rightHit) {
        rec = rrec;
        return true;
    }
    else {
        return false;
    }
}

BoundingBox BVHNode::createBoundingBox() {
    return bbox;
}

Vector4 BVHNode::getCenter() {
    return (left->getCenter() + right->getCenter()) / 2.0;
}


void BVHNode::setLeft(std::shared_ptr<Shape> shape) {
    left = shape;
}

void BVHNode::setRight(std::shared_ptr<Shape> shape) {
    right = shape;
}

void BVHNode::setBBox(const BoundingBox& box) {
    bbox = box;
}
