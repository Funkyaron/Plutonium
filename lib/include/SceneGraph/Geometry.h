



#ifndef PLUTONIUM_GEOMETRY_H
#define PLUTONIUM_GEOMETRY_H


#include "Mesh.h"


class Material;



enum class PrimitiveType {
    SPHERE,
    RECTANGLE
};




class Geometry {
public:

    void setMaterial(std::shared_ptr<Material> material_);
    std::shared_ptr<Material> getMaterial();

protected:
    Geometry() {} // Make class "abstract"

private:

    std::shared_ptr<Material> material; // Just borrowing from the raytracer for now

};



class Primitive : public Geometry {
public:

    Primitive(PrimitiveType type_) : type(type_) {}

    void setType(PrimitiveType type_);
    PrimitiveType getType();

private:

    PrimitiveType type;

};


class MeshGeometry : public Geometry {
public:

    MeshGeometry(std::shared_ptr<Mesh> meshData_) : meshData(meshData_) {}

    void setMeshData(std::shared_ptr<Mesh> meshData_);
    std::shared_ptr<Mesh> getMeshData();

private:

    std::shared_ptr<Mesh> meshData;

};



#endif