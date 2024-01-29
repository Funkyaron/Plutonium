


#include <fstream>



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


TriangleFanMesh::TriangleFanMesh(std::string objFilename) {

    vertices = {};
    indices = {};

    std::ifstream is(objFilename);
    std::string str;
    while(std::getline(is, str)) {
        if(str.starts_with("v ")) {
            str.erase(0, str.find_first_not_of("abcdefghijklmnopqrstuvwxyz "));
            std::string delimiter = " ";
            std::string xStr = str.substr(0, str.find(delimiter));
            str.erase(0, str.find(delimiter) + delimiter.length());
            std::string yStr = str.substr(0, str.find(delimiter));
            str.erase(0, str.find(delimiter) + delimiter.length());
            std::string zStr = str.substr(0, str.find(delimiter));
            float x = std::stof(xStr);
            float y = std::stof(yStr);
            float z = std::stof(zStr);
            vertices.push_back(Vector4(x, y, z, 1.0));
        }
        else if(str.starts_with("f ")) {
            str.erase(0, str.find_first_not_of("abcdefghijklmnopqrstuvwxyz "));
            std::vector<int> indices = {};
            while(str.empty() == false) {
                std::string informationBitDelimiter = "/";
                std::string vertexDelimiter = " ";
                std::string vertexIndexStr = str.substr(0, str.find(informationBitDelimiter));
                indices.push_back(std::stoi(vertexIndexStr));
                str.erase(0, str.find(vertexDelimiter) + vertexDelimiter.length());
            }
            indices.push_back(-1);
        }
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

Vector4 TriangleFanMesh::getCenter() {
    Vector4 sum(0.0, 0.0, 0.0, 0.0);
    for(auto& vertex : vertices) {
        sum += vertex;
    }
    return sum / float(vertices.size());
}
