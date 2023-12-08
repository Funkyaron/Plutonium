


#include "Mesh.h"
#include "Shape.h"




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


void IndexedTriangleMesh::makeShapeCollection(std::vector<std::shared_ptr<Shape> >& targetShapes) {
    targetShapes = {};

    for(auto& currentTriInd : triangleIndices) {
        targetShapes.push_back(std::make_shared<Triangle>(vertices[currentTriInd[0]], vertices[currentTriInd[1]], vertices[currentTriInd[2]]));
    }
}

Vector4 IndexedTriangleMesh::getCenter() {
    Vector4 sum(0.0, 0.0, 0.0, 0.0);
    for(auto& vertex : vertices) {
        sum += vertex;
    }
    return sum / float(vertices.size());
}