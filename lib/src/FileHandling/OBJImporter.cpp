




#include "OBJImporter.h"
#include "Vector3.h"
#include "Mesh.h"



#include <fstream>
#include <sstream>
#include <iostream>
#include <cctype>
#include <vector>



std::shared_ptr<Mesh> OBJImporter::importOBJ(const std::string& filename) {

    std::ifstream inputStream(filename);

    std::stringstream currentStringStream;
    std::vector<float> currentCoordinates = {};
    std::vector<Vector3> vertices = {};
    std::vector<Vector3> normals = {};
    std::vector<Vector3> texcoords = {};

    TriangleIndex currentFaceVertex;
    std::vector<TriangleIndex> currentFace = {};
    std::vector<std::array<TriangleIndex, 3> > triangles = {};

    OBJImporterState currentState = OBJImporterState::START;
    bool isFileValid = true;

    char c;
    while(inputStream.get(c)) {

        if(currentState == OBJImporterState::START) {
            if(c == '#') {
                currentState = OBJImporterState::SKIP_LINE;
            }
            else if(c == 'v') {
                currentState = OBJImporterState::V;
            }
            else if(c == 'f') {
                currentState = OBJImporterState::FACE;
            }
            else if(std::isspace(c)) {
                // Do nothing
            }
            else if(std::string("mogus").contains(c)) {
                currentState = OBJImporterState::NOT_YET_IMPLEMENTED;
            }
            else {
                isFileValid = false;
            }
        }

        else if(currentState == OBJImporterState::SKIP_LINE) {
            if(c == '\n') {
                currentState = OBJImporterState::START;
            }
        }

        else if(currentState == OBJImporterState::V) {
            if(c == ' ') {
                currentState = OBJImporterState::VERT;
            }
            else if(c == 'n') {
                currentState = OBJImporterState::NORM;
            }
            else if(c == 't') {
                currentState = OBJImporterState::TEX;
            }
        }

        else if(currentState == OBJImporterState::VERT) {
            if(c == ' ') {
                // Do nothing
            }
            else if(std::string("-0123456789").contains(c)) {
                currentStringStream << c;
                currentState = OBJImporterState::REC_VERT_COORD;
            }
            else {
                isFileValid = false;
            }
        }

        else if(currentState == OBJImporterState::REC_VERT_COORD) {
            if(std::string("0123456789.").contains(c)) {
                currentStringStream << c;
            }
            else if(c == ' ') {
                std::string tokenString = currentStringStream.str();
                currentStringStream.str("");
                currentCoordinates.push_back(std::stof(tokenString));
                currentState = OBJImporterState::VERT_COORD_SEP;
            }
            else if(c == '\n') {
                std::string tokenString = currentStringStream.str();
                currentStringStream.str("");
                currentCoordinates.push_back(std::stof(tokenString));

                if(currentCoordinates.size() == 3) {
                    vertices.push_back(Vector3(currentCoordinates[0], currentCoordinates[1], currentCoordinates[2]));
                }
                else {
                    isFileValid = false;
                }
                currentCoordinates.clear();
                currentState = OBJImporterState::START;
            }
            else {
                isFileValid = false;
            }
        }

        else if(currentState == OBJImporterState::VERT_COORD_SEP) {
            if(std::string("-0123456789").contains(c)) {
                currentStringStream << c;
                currentState = OBJImporterState::REC_VERT_COORD;
            }
            else if(c == ' ') {
                // Do nothing
            }
            else if(c == '\n') {

                if(currentCoordinates.size() == 3) {
                    vertices.push_back(Vector3(currentCoordinates[0], currentCoordinates[1], currentCoordinates[2]));
                }
                else {
                    isFileValid = false;
                }
                currentCoordinates.clear();
                currentState = OBJImporterState::START;
            }
            else {
                isFileValid = false;
            }
        }

        else if(currentState == OBJImporterState::NORM) {
            if(c == ' ') {
                // Do nothing
            }
            else if(std::string("-0123456789").contains(c)) {
                currentStringStream << c;
                currentState = OBJImporterState::REC_NORM_COORD;
            }
            else {
                isFileValid = false;
            }
        }

        else if(currentState == OBJImporterState::REC_NORM_COORD) {
            if(std::string("0123456789.").contains(c)) {
                currentStringStream << c;
            }
            else if(c == ' ') {
                std::string tokenString = currentStringStream.str();
                currentStringStream.str("");
                currentCoordinates.push_back(std::stof(tokenString));
                currentState = OBJImporterState::NORM_COORD_SEP;
            }
            else if(c == '\n') {
                std::string tokenString = currentStringStream.str();
                currentStringStream.str("");
                currentCoordinates.push_back(std::stof(tokenString));

                if(currentCoordinates.size() == 3) {
                    normals.push_back(Vector3(currentCoordinates[0], currentCoordinates[1], currentCoordinates[2]));
                }
                else {
                    isFileValid = false;
                }
                currentCoordinates.clear();
                currentState = OBJImporterState::START;
            }
            else {
                isFileValid = false;
            }
        }

        else if(currentState == OBJImporterState::NORM_COORD_SEP) {
            if(std::string("-0123456789").contains(c)) {
                currentStringStream << c;
                currentState = OBJImporterState::REC_NORM_COORD;
            }
            else if(c == ' ') {
                // Do nothing
            }
            else if(c == '\n') {

                if(currentCoordinates.size() == 3) {
                    normals.push_back(Vector3(currentCoordinates[0], currentCoordinates[1], currentCoordinates[2]));
                }
                else {
                    isFileValid = false;
                }
                currentCoordinates.clear();
                currentState = OBJImporterState::START;
            }
            else {
                isFileValid = false;
            }
        }

        else if(currentState == OBJImporterState::TEX) {
            if(c == ' ') {
                // Do nothing
            }
            else if(std::string("-0123456789").contains(c)) {
                currentStringStream << c;
                currentState = OBJImporterState::REC_TEX_COORD;
            }
            else {
                isFileValid = false;
            }
        }

        else if(currentState == OBJImporterState::REC_TEX_COORD) {
            if(std::string("0123456789.").contains(c)) {
                currentStringStream << c;
            }
            else if(c == ' ') {
                std::string tokenString = currentStringStream.str();
                currentStringStream.str("");
                currentCoordinates.push_back(std::stof(tokenString));
                currentState = OBJImporterState::TEX_COORD_SEP;
            }
            else if(c == '\n') {
                std::string tokenString = currentStringStream.str();
                currentStringStream.str("");
                currentCoordinates.push_back(std::stof(tokenString));

                if(currentCoordinates.size() == 3) {
                    texcoords.push_back(Vector3(currentCoordinates[0], currentCoordinates[1], currentCoordinates[2]));
                }
                else if(currentCoordinates.size() == 2) {
                    texcoords.push_back(Vector3(currentCoordinates[0], currentCoordinates[1], 0.0));
                }
                else {
                    isFileValid = false;
                }
                currentCoordinates.clear();
                currentState = OBJImporterState::START;
            }
            else {
                isFileValid = false;
            }
        }

        else if(currentState == OBJImporterState::TEX_COORD_SEP) {
            if(std::string("-0123456789").contains(c)) {
                currentStringStream << c;
                currentState = OBJImporterState::REC_TEX_COORD;
            }
            else if(c == ' ') {
                // Do nothing
            }
            else if(c == '\n') {

                if(currentCoordinates.size() == 3) {
                    texcoords.push_back(Vector3(currentCoordinates[0], currentCoordinates[1], currentCoordinates[2]));
                }
                else if(currentCoordinates.size() == 2) {
                    texcoords.push_back(Vector3(currentCoordinates[0], currentCoordinates[1], 0.0));
                }
                else {
                    isFileValid = false;
                }
                currentCoordinates.clear();
                currentState = OBJImporterState::START;
            }
            else {
                isFileValid = false;
            }
        }

        else if(currentState == OBJImporterState::FACE) {
            if(c == ' ') {
                // Do nothing
            }
            else if(std::string("0123456789").contains(c)) {
                currentStringStream << c;
                currentState = OBJImporterState::REC_FACE_VERT_IND;
            }
            else {
                isFileValid = false;
            }
        }

        else if(currentState == OBJImporterState::REC_FACE_VERT_IND) {
            if(std::string("0123456789").contains(c)) {
                currentStringStream << c;
            }
            else if(c == '/') {
                std::string tokenString = currentStringStream.str();
                currentStringStream.str("");
                currentFaceVertex.vert = std::stoi(tokenString);
                currentState = OBJImporterState::MAYBE_FACE_TEX_IND;
            }
            else if(c == ' ') {
                std::string tokenString = currentStringStream.str();
                currentStringStream.str("");
                currentFaceVertex.vert = std::stoi(tokenString);
                currentFaceVertex.norm = 0;
                currentFaceVertex.tex = 0;
                currentFace.push_back(currentFaceVertex);
                currentState = OBJImporterState::FACE_VERT_SEP;
            }
            else if(c == '\n') {
                std::string tokenString = currentStringStream.str();
                currentStringStream.str("");
                currentFaceVertex.vert = std::stoi(tokenString);
                currentFaceVertex.norm = 0;
                currentFaceVertex.tex = 0;
                currentFace.push_back(currentFaceVertex);

                isFileValid = triangulateAndAdd(currentFace, triangles);
                currentFace = {};

                currentState = OBJImporterState::START;
            }
            else {
                isFileValid = false;
            }
        }

        else if(currentState == OBJImporterState::MAYBE_FACE_TEX_IND) {
            if(std::string("0123456789").contains(c)) {
                currentStringStream << c;
                currentState = OBJImporterState::REC_FACE_TEX_IND;
            }
            else if(c == '/') {
                currentFaceVertex.tex = 0;
                currentState = OBJImporterState::REC_FACE_NORM_IND;
            }
            else {
                isFileValid = false;
            }
        }

        else if(currentState == OBJImporterState::REC_FACE_TEX_IND) {
            if(std::string("0123456789").contains(c)) {
                currentStringStream << c;
            }
            else if(c == '/') {
                std::string tokenString = currentStringStream.str();
                currentStringStream.str("");
                currentFaceVertex.tex = std::stoi(tokenString);
                currentState = OBJImporterState::REC_FACE_NORM_IND;
            }
            else if(c == ' ') {
                std::string tokenString = currentStringStream.str();
                currentStringStream.str("");
                currentFaceVertex.tex = std::stoi(tokenString);
                currentFaceVertex.norm = 0;
                currentFace.push_back(currentFaceVertex);
                currentState = OBJImporterState::FACE_VERT_SEP;
            }
            else if(c == '\n') {
                std::string tokenString = currentStringStream.str();
                currentStringStream.str("");
                currentFaceVertex.tex = std::stoi(tokenString);
                currentFaceVertex.norm = 0;
                currentFace.push_back(currentFaceVertex);

                isFileValid = triangulateAndAdd(currentFace, triangles);
                currentFace = {};

                currentState = OBJImporterState::START;
            }
            else {
                isFileValid = false;
            }
        }

        else if(currentState == OBJImporterState::REC_FACE_NORM_IND) {
            if(std::string("0123456789").contains(c)) {
                currentStringStream << c;
            }
            else if(c == ' ') {
                std::string tokenString = currentStringStream.str();
                currentStringStream.str("");
                currentFaceVertex.norm = std::stoi(tokenString);
                currentFace.push_back(currentFaceVertex);
                currentState = OBJImporterState::FACE_VERT_SEP;
            }
            else if(c == '\n') {
                std::string tokenString = currentStringStream.str();
                currentStringStream.str("");
                currentFaceVertex.norm = std::stoi(tokenString);
                currentFace.push_back(currentFaceVertex);

                isFileValid = triangulateAndAdd(currentFace, triangles);
                currentFace = {};

                currentState = OBJImporterState::START;
            }
            else {
                isFileValid = false;
            }
        }

        else if(currentState == OBJImporterState::FACE_VERT_SEP) {
            if(c == ' ') {
                // Do nothing
            }
            else if(std::string("0123456789").contains(c)) {
                currentStringStream << c;
                currentState = OBJImporterState::REC_FACE_VERT_IND;
            }
            else if(c == '\n') {

                isFileValid = triangulateAndAdd(currentFace, triangles);
                currentFace = {};

                currentState = OBJImporterState::START;
            }
            else {
                isFileValid = false;
            }
        }

        else if(currentState == OBJImporterState::NOT_YET_IMPLEMENTED) {
            if(c == '\n') {
                currentState = OBJImporterState::START;
            }
        }

        if(isFileValid == false) {
            std::cout << "File invalid\n";
            inputStream.close();
            return nullptr;
        }
    }

    inputStream.close();


    std::shared_ptr<IndexedTriangleMesh> result = std::make_shared<IndexedTriangleMesh>();
    result->setVertices(std::move(vertices));
    result->setNormals(std::move(normals));
    result->setTexcoords(std::move(texcoords));
    result->setTriangleIndices(std::move(triangles));

    return result;
}




bool OBJImporter::triangulateAndAdd(std::vector<TriangleIndex>& face, std::vector<std::array<TriangleIndex, 3> >& allTriangles) {
    if(face.size() < 3) {
        return false;
    }

    auto it = face.begin() + 2;

    while(it != face.end()) {
        allTriangles.push_back({face[0], *(it - 1), *(it)});
        it++;
    }

    return true;
}