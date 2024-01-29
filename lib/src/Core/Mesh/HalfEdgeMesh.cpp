



#include "Mesh.h"
#include "Shape.h"




HalfEdgeMesh::HalfEdgeMesh(MeshType type) {
    if(type == MeshType::Cube) {
        vertices = { // pos, HEdgeIndex
            {Vector4(-1.0, -1.0, -1.0, 1.0), 0}, // 0
            {Vector4(-1.0, -1.0, 1.0, 1.0), 1}, // 1
            {Vector4(-1.0, 1.0, -1.0, 1.0), 3}, // 2
            {Vector4(-1.0, 1.0, 1.0, 1.0), 2}, // 3
            {Vector4(1.0, -1.0, -1.0, 1.0), 9}, // 4
            {Vector4(1.0, -1.0, 1.0, 1.0), 8}, // 5
            {Vector4(1.0, 1.0, -1.0, 1.0), 10}, // 6
            {Vector4(1.0, 1.0, 1.0, 1.0), 11} // 7
        };
        edges = { // pairHEdgeIndex, nextHEdgeIndex, vertexIndex, faceIndex
            {14, 1, 0, 4}, // 0
            {21, 2, 1, 4}, // 1
            {4, 3, 3, 4}, // 2
            {17, 0, 2, 4}, // 3

            {2, 4, 1, 1}, // 4
            {20, 6, 5, 1}, // 5
            {8, 7, 7, 1}, // 6
            {18, 4, 3, 1}, // 7

            {6, 9, 5, 2}, // 8
            {23, 10, 4, 2}, // 9
            {12, 11, 6, 2}, // 10
            {19, 8, 7, 2}, // 11

            {10, 13, 4, 3}, // 12
            {22, 14, 0, 3}, // 13
            {0, 15, 2, 3}, // 14
            {16, 12, 6, 3}, // 15

            {15, 17, 2, 0}, // 16
            {3, 18, 3, 0}, // 17
            {7, 19, 7, 0}, // 18
            {11, 16, 6, 0}, // 19

            {5, 21, 1, 5}, // 20
            {1, 22, 0, 5}, // 21
            {13, 13, 4, 5}, // 22
            {9, 20, 5, 5} // 23
        };
        faces = { // HEdgeIndex
            {18}, // 0
            {6}, // 1
            {10}, // 2
            {14}, // 3
            {2}, // 4
            {23} // 5
        };
    }
}

void HalfEdgeMesh::traverseEdgesOfFace(const Face& face, std::function<void(const HEdge&)> edgeCallback) {
    int currentHEdgeIndex = face.HEdgeIndex;
    do {
        edgeCallback(edges[currentHEdgeIndex]);
        currentHEdgeIndex = edges[currentHEdgeIndex].nextHEdgeIndex;
    } while(currentHEdgeIndex != face.HEdgeIndex);
}

void HalfEdgeMesh::makeShapeCollection(std::vector<std::shared_ptr<Shape> >& targetShapes) {
    // The plan is: Go through all faces, use the EdgesOfFace traversal and treat the corresponding vertices as traingle fans
    // as a crude way to trainglulate the mesh because this structure allows arbitrary polygons

    std::vector<int> triangleFanIndices = {};
    for(auto& currentFace : faces) {
        traverseEdgesOfFace(currentFace, [&](const HEdge& edge) {
            triangleFanIndices.push_back(edge.vertexIndex);
        });
        triangleFanIndices.push_back(-1);
    }

    targetShapes = {};

    auto indicesIt = triangleFanIndices.begin();

    while(indicesIt != triangleFanIndices.end()) {
        int currentBaseIndex = *indicesIt;
        indicesIt += 2;
        while(*indicesIt != -1) {
            targetShapes.push_back(std::make_shared<Triangle>(vertices[currentBaseIndex].pos, vertices[*(indicesIt - 1)].pos, vertices[*indicesIt].pos));
            indicesIt++;
        }
        indicesIt++;
    }
}

Vector4 HalfEdgeMesh::getCenter() {
    Vector4 sum(0.0, 0.0, 0.0, 0.0);
    for(auto& vertex : vertices) {
        sum += vertex.pos;
    }
    return sum / float(vertices.size());
}