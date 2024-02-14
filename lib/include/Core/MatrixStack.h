


#ifndef PLUTONIUM_MATRIXSTACK_H
#define PLUTONIUM_MATRIXSTACK_H


#include "Matrix4.h"
#include "Transform.h"

#include <memory>
#include <stack>


class MatrixStack {
public:

    MatrixStack();

    void push(std::shared_ptr<Transform> transform);
    void pop();

    Matrix4 getTopMatrix();

private:

    std::stack<Matrix4> matrices;

};




#endif