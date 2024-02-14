




#ifndef PLUTONIUM_SCENEGRAPHNODE_H
#define PLUTONIUM_SCENEGRAPHNODE_H


#include <functional>
#include <memory>
#include <vector>
#include <string>

#include "Geometry.h"
#include "Camera.h"
#include "MatrixStack.h"
#include "Transform.h"




class SceneGraphNode : public std::enable_shared_from_this<SceneGraphNode> {
public:

    virtual void traverse(MatrixStack& matStack, std::function<void(std::shared_ptr<SceneGraphNode>, Matrix4)> callback) = 0;

    void setId(std::string id_);
    std::string getId();

    std::shared_ptr<Transform> getTransform();

protected:

    std::shared_ptr<Transform> transform;

private:

    std::string id;

};



class EmptyNode : public SceneGraphNode {
public:

    EmptyNode();

    virtual void traverse(MatrixStack& matStack, std::function<void(std::shared_ptr<SceneGraphNode>, Matrix4)> callback) override;

    void addChildNode(std::shared_ptr<SceneGraphNode> node);
    void clearChildNodes();

private:

    std::vector<std::shared_ptr<SceneGraphNode> > childNodes;

};



class GeometryNode : public SceneGraphNode {
public:

    GeometryNode(std::shared_ptr<Geometry> geometry_);

    virtual void traverse(MatrixStack& matStack, std::function<void(std::shared_ptr<SceneGraphNode>, Matrix4)> callback) override;

    void setGeometry(std::shared_ptr<Geometry> geometry_);
    std::shared_ptr<Geometry> getGeometry();

private:

    std::shared_ptr<Geometry> geometry;

};


class CameraNode : public SceneGraphNode {
public:

    CameraNode(std::shared_ptr<Camera> camera_);

    virtual void traverse(MatrixStack& matStack, std::function<void(std::shared_ptr<SceneGraphNode>, Matrix4)> callback) override;

    void setCamera(std::shared_ptr<Camera> camera_);
    std::shared_ptr<Camera> getCamera();

private:

    std::shared_ptr<Camera> camera;

};





#endif