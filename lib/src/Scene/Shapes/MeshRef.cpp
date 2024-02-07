




#include <iostream>


#include "Shape.h"
#include "Ray.h"
#include "Mesh.h"





bool MeshRef::hit(Ray r, float t0, float t1, HitRecord& rec) const {
    std::cout << "[ERROR]: Not allowed to call hit on MeshRef\n";
    return false;
}

BoundingBox MeshRef::createBoundingBox() {
    std::cout << "[ERROR]: Not allowed to create BoundingBox of MeshRef\n";
    return BoundingBox(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
}

Vector4 MeshRef::getCenter() {
    return mesh->getCenter();
}

std::shared_ptr<Shape> MeshRef::buildBVH(int axis, std::vector<BoundingBox>& importantBoxes, std::function<bool(std::shared_ptr<ShapeInstance>)> ruleset) {
    std::vector<std::shared_ptr<Shape> > shapeCollection;

    mesh->makeShapeCollection(shapeCollection);

    return BVHNode::create(shapeCollection, axis, importantBoxes, ruleset);
}