


#include "SceneGraph.h"
#include "SceneGraphNode.h"
#include "MatrixStack.h"



void SceneGraph::traverseGraph(std::function<void(std::shared_ptr<SceneGraphNode>, Matrix4)> callback) {
    if(root == nullptr) {
        return;
    }
    MatrixStack matStack; // Constructor should set the identity matrix as inital stack element
    root->traverse(matStack, callback);
}

void SceneGraph::setRoot(std::shared_ptr<SceneGraphNode> root_) {
    root = root_;
}

void SceneGraph::setActiveCamera(std::shared_ptr<RendererCamera> activeCamera_) {
    activeCamera = activeCamera_;
}

std::shared_ptr<RendererCamera> SceneGraph::getActiveCamera() {
    return activeCamera;
}