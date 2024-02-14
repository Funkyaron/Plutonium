

#include "SceneGraphNode.h"


CameraNode::CameraNode(std::shared_ptr<Camera> camera_) {
    camera = camera_;
    transform = std::make_shared<Transform>();
}


void CameraNode::traverse(MatrixStack& matStack, std::function<void(std::shared_ptr<SceneGraphNode>, Matrix4)> callback) {
    matStack.push(transform);
    callback(shared_from_this(), matStack.getTopMatrix());
    matStack.pop();
}

void CameraNode::setCamera(std::shared_ptr<Camera> camera_) {
    camera = camera_;
}

std::shared_ptr<Camera> CameraNode::getCamera() {
    return camera;
}