

#include "SceneGraphNode.h"


EmptyNode::EmptyNode() {
    childNodes = {};
    transform = std::make_shared<Transform>();
}


void EmptyNode::traverse(MatrixStack& matStack, std::function<void(std::shared_ptr<SceneGraphNode>, Matrix4)> callback) {
    matStack.push(transform);
    callback(shared_from_this(), matStack.getTopMatrix());
    for(auto &childNode : childNodes) {
        traverse(matStack, callback);
    }
    matStack.pop();
}

void EmptyNode::addChildNode(std::shared_ptr<SceneGraphNode> node) {
    childNodes.push_back(node);
}

void EmptyNode::clearChildNodes() {
    childNodes.clear();
}