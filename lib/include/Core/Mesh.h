

#ifndef PLUTONIUM_MESH_H
#define PLUTONIUM_MESH_H


#include <vector>
#include <memory>
#include <array>

#include "Vector4.h"


class Shape;



enum class MeshType {
    Cube
};



class Mesh {
public:

    virtual void makeShapeCollection(std::vector<std::shared_ptr<Shape> >& targetShapes) = 0;

    const std::vector<Vector4>& getVertices() { return vertices; }

protected:

    std::vector<Vector4> vertices;

};



class IndexedTriangleMesh : public Mesh {
public:

    IndexedTriangleMesh(MeshType type);

    virtual void makeShapeCollection(std::vector<std::shared_ptr<Shape> >& targetShapes) override;

private:

    std::vector<std::array<int, 3> > triangleIndices;

};





#endif