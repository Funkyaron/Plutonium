



#include <algorithm>
#include <limits>


#include "Shape.h"
#include "Ray.h"




IndexedTriangleMesh::IndexedTriangleMesh(MeshType type) {
    if(type == MeshType::Cube) {
        vertices = {
            Vector4(-1.0, -1.0, -1.0, 1.0), // 0
            Vector4(-1.0, -1.0, 1.0, 1.0), // 1
            Vector4(-1.0, 1.0, -1.0, 1.0), // 2
            Vector4(-1.0, 1.0, 1.0, 1.0), // 3
            Vector4(1.0, -1.0, -1.0, 1.0), // 4
            Vector4(1.0, -1.0, 1.0, 1.0), // 5
            Vector4(1.0, 1.0, -1.0, 1.0), // 6
            Vector4(1.0, 1.0, 1.0, 1.0) // 7
        };
        triangleIndices = {
            {0, 6, 4}, // z = -1
            {0, 2, 6},
            {1, 5, 7}, // z = 1
            {1, 7, 3},
            {1, 3, 2}, // x = -1
            {1, 2, 0},
            {5, 4, 6}, // x = 1
            {5, 6, 7},
            {0, 4, 5}, // y = -1
            {0, 5, 1},
            {3, 7, 6}, // y = 1
            {3, 6, 2}
        };
    }
}

bool IndexedTriangleMesh::hit(Ray r, float t0, float t1, HitRecord& rec) const {
    HitRecord tempRec;
    bool hitAnything = false;
    float closestSoFar = t1;
    for(auto& currentTriInd : triangleIndices) {
        if(hitTriangle(r, t0, closestSoFar, tempRec, vertices[currentTriInd[0]], vertices[currentTriInd[1]], vertices[currentTriInd[2]])) {
            hitAnything = true;
            closestSoFar = tempRec.t;
            rec = tempRec;
        }
    }
    return hitAnything;
}

BoundingBox IndexedTriangleMesh::createBoundingBox() {
    float xmin = std::numeric_limits<float>::max();
    float xmax = std::numeric_limits<float>::lowest();
    float ymin = std::numeric_limits<float>::max();
    float ymax = std::numeric_limits<float>::lowest();
    float zmin = std::numeric_limits<float>::max();
    float zmax = std::numeric_limits<float>::lowest();

    for(auto& vertex : vertices) {
        xmin = std::min(xmin, vertex.x());
        xmax = std::max(xmax, vertex.x());
        ymin = std::min(ymin, vertex.y());
        ymax = std::max(ymax, vertex.y());
        zmin = std::min(zmin, vertex.z());
        zmax = std::max(zmax, vertex.z());
    }

    return BoundingBox(xmin, xmax, ymin, ymax, zmin, zmax);
}

Vector4 IndexedTriangleMesh::getCenter() {
    Vector4 vertSum = Vector4(0.0, 0.0, 0.0, 0.0);
    for(auto& vertex : vertices) {
        vertSum += vertex;
    }
    return vertSum / float(vertices.size());
}