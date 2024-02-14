



#include "MatrixStack.h"



MatrixStack::MatrixStack() {
    matrices.push(Matrix4::identity());
}

void MatrixStack::push(std::shared_ptr<Transform> transform) {
    matrices.push(transform->getAsMatrix4() * matrices.top());
}

void MatrixStack::pop() {
    matrices.pop();
}

Matrix4 MatrixStack::getTopMatrix() {
    return matrices.top();
}