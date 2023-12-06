




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
    Vector4 sum(0.0, 0.0, 0.0, 0.0);
    const std::vector<Vector4>& meshVertices = mesh->getVertices();
    for(auto& vertex : meshVertices) {
        sum += vertex;
    }
    return sum / float(meshVertices.size());
}

std::shared_ptr<Shape> MeshRef::buildBVH(int axis) {
    std::vector<std::shared_ptr<Shape> > shapeCollection;

    mesh->makeShapeCollection(shapeCollection);

    return BVHNode::create(shapeCollection, axis);
}