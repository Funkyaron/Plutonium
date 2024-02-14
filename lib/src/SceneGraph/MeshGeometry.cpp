

#include "Geometry.h"


void MeshGeometry::setMeshData(std::shared_ptr<Mesh> meshData_) {
    meshData = meshData_;
}

std::shared_ptr<Mesh> MeshGeometry::getMeshData() {
    return meshData;
}