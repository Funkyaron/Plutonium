

#include "Mesh.h"
#include "Shape.h"



TriangleFanMesh::TriangleFanMesh(MeshType type) {
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

        indices = {};

        // Fan 1
        indices.push_back(0);
        indices.push_back(4);
        indices.push_back(5);
        indices.push_back(1);
        indices.push_back(3);
        indices.push_back(2);
        indices.push_back(6);
        indices.push_back(4);

        // Terminator
        indices.push_back(-1);

        // Fan 2
        indices.push_back(7);
        indices.push_back(3);
        indices.push_back(1);
        indices.push_back(5);
        indices.push_back(4);
        indices.push_back(6);
        indices.push_back(2);
        indices.push_back(3);

        // Terminator
        indices.push_back(-1);
    }
}


void TriangleFanMesh::makeShapeCollection(std::vector<std::shared_ptr<Shape> >& targetShapes) {
    targetShapes = {};

    auto indicesIt = indices.begin();

    while(indicesIt != indices.end()) {
        int currentBaseIndex = *indicesIt;
        indicesIt += 2;
        while(*indicesIt != -1) {
            targetShapes.push_back(std::make_shared<Triangle>(vertices[currentBaseIndex], vertices[*(indicesIt - 1)], vertices[*indicesIt]));
            indicesIt++;
        }
        indicesIt++;
    }
}
