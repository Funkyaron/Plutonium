



#include "Mesh.h"
#include "Shape.h"




TriangleStripMesh::TriangleStripMesh(MeshType type) {
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

        // Strip 1
        indices.push_back(6);
        indices.push_back(2);
        indices.push_back(7);
        indices.push_back(3);
        indices.push_back(5);
        indices.push_back(1);
        indices.push_back(4);
        indices.push_back(0);

        // Terminator
        indices.push_back(-1);

        // Strip 2
        indices.push_back(1);
        indices.push_back(3);
        indices.push_back(0);
        indices.push_back(2);
        indices.push_back(4);
        indices.push_back(6);
        indices.push_back(5);
        indices.push_back(7);

        // Terminator
        indices.push_back(-1);
    }
}

void TriangleStripMesh::makeShapeCollection(std::vector<std::shared_ptr<Shape> >& targetShapes) {
    targetShapes = {};

    auto indicesIt = indices.begin();

    while(indicesIt != indices.end()) {
        indicesIt += 2;
        bool reverseOrder = false;
        while(*indicesIt != -1) {
            if(reverseOrder) {
                targetShapes.push_back(std::make_shared<Triangle>(vertices[*(indicesIt - 1)], vertices[*(indicesIt - 2)], vertices[*(indicesIt)]));
            }
            else {
                targetShapes.push_back(std::make_shared<Triangle>(vertices[*(indicesIt - 2)], vertices[*(indicesIt - 1)], vertices[*(indicesIt)]));
            }
            reverseOrder = !reverseOrder;
        }
        indicesIt++;
    }
}