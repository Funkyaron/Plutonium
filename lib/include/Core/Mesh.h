

#ifndef PLUTONIUM_MESH_H
#define PLUTONIUM_MESH_H


#include <vector>
#include <memory>
#include <array>
#include <functional>
#include <string>

#include "Vector4.h"


class Shape;



enum class MeshType {
    Cube
};



class Mesh {
public:

    virtual void makeShapeCollection(std::vector<std::shared_ptr<Shape> >& targetShapes) = 0;
    virtual Vector4 getCenter() = 0;

protected:

};



class IndexedTriangleMesh : public Mesh {
public:

    IndexedTriangleMesh(MeshType type);

    virtual void makeShapeCollection(std::vector<std::shared_ptr<Shape> >& targetShapes) override;
    virtual Vector4 getCenter() override;

private:

    std::vector<Vector4> vertices;
    std::vector<std::array<int, 3> > triangleIndices;


};



class TriangleFanMesh : public Mesh {
public:

    TriangleFanMesh(MeshType type);
    TriangleFanMesh(std::string objFilename);

    virtual void makeShapeCollection(std::vector<std::shared_ptr<Shape> >& targetShapes) override;
    virtual Vector4 getCenter() override;

private:

    std::vector<Vector4> vertices;
    std::vector<int> indices; // Fans are termitated by an index of -1 to prevent memory management hazard

};



class TriangleStripMesh : public Mesh {
public:

    TriangleStripMesh(MeshType type);

    virtual void makeShapeCollection(std::vector<std::shared_ptr<Shape> >& targetShapes) override;
    virtual Vector4 getCenter() override;

private:

    std::vector<Vector4> vertices;
    std::vector<int> indices; // Strips are termitated by an index of -1 to prevent memory management hazard

};



typedef struct {
    int pairHEdgeIndex;
    int nextHEdgeIndex;
    int vertexIndex;
    int faceIndex;
} HEdge;

typedef struct {
    Vector4 pos;
    // per vertex data
    int HEdgeIndex;
} Vertex;

typedef struct {
    // per face data
    int HEdgeIndex;
} Face;


class HalfEdgeMesh : public Mesh {
public:

    HalfEdgeMesh(MeshType type);

    void traverseEdgesOfFace(const Face& face, std::function<void(const HEdge&)> edgeCallback);

    virtual void makeShapeCollection(std::vector<std::shared_ptr<Shape> >& targetShapes) override;
    virtual Vector4 getCenter() override;

private:

    std::vector<Vertex> vertices;
    std::vector<Face> faces;
    std::vector<HEdge> edges;

};








#endif