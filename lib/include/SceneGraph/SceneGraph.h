



#ifndef PLUTONIUM_SCENEGRAPH_H
#define PLUTONIUM_SCENEGRAPH_H



#include "Matrix4.h"

#include <functional>
#include <memory>


class SceneGraphNode;
class RendererCamera;



// The Scene graph should be abstract enough so that it can
// be rendered by a raytracing renderer as well as a rasterizing
// renderer, e.g. for viewport scene preview
// The respective renderer should transform this SceneGraph to
// an internal representation including implementation specific
// structures such as Bounding Volume Hierarchies for raytracing


class SceneGraph {
public:

    SceneGraph() : root(nullptr), activeCamera(nullptr) {}
    SceneGraph(std::shared_ptr<SceneGraphNode> root_, std::shared_ptr<RendererCamera> activeCamera_) : root(root_), activeCamera(activeCamera_) {}

    void traverseGraph(std::function<void(std::shared_ptr<SceneGraphNode>, Matrix4)> callback);

    void setRoot(std::shared_ptr<SceneGraphNode> root_);
    // I don't see why I should allow anyone to get the root node directly

    void setActiveCamera(std::shared_ptr<RendererCamera> activeCamera_);
    std::shared_ptr<RendererCamera> getActiveCamera();

private:

    std::shared_ptr<SceneGraphNode> root;
    std::shared_ptr<RendererCamera> activeCamera; // I don't have an Idea what to put in the Camera SceneGraphNode just yet, so make it an explicit raytracing renderer camera.

};






#endif