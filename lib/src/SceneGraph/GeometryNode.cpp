



#include "SceneGraphNode.h"


GeometryNode::GeometryNode(std::shared_ptr<Geometry> geometry_) {
    geometry = geometry;
    transform = std::make_shared<Transform>();
}


void GeometryNode::traverse(MatrixStack& matStack, std::function<void(std::shared_ptr<SceneGraphNode>, Matrix4)> callback) {
    matStack.push(transform);
    callback(shared_from_this(), matStack.getTopMatrix());
    matStack.pop();
}

void GeometryNode::setGeometry(std::shared_ptr<Geometry> geometry_) {
    geometry = geometry_;
}

std::shared_ptr<Geometry> GeometryNode::getGeometry() {
    return geometry;
}