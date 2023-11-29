



#include "Transform.h"
#include "Matrix4.h"



Transform::Transform() {
    locationX = locationY = locationZ = 0.0;
    rotationX = rotationY = rotationZ = 0.0;
    scaleX = scaleY = scaleZ = 1.0;

    inverseMatrix = Matrix4::identity();
    matrix = Matrix4::identity();

    inverseMatrixCalculated = true;
    matrixCalculated = true;
}

void Transform::setLocationX(float loc) {
    if(loc != locationX) {
        locationX = loc;
        inverseMatrixCalculated = false;
        matrixCalculated = false;
    }
}

void Transform::setLocationY(float loc) {
    if(loc != locationY) {
        locationY = loc;
        inverseMatrixCalculated = false;
        matrixCalculated = false;
    }
}

void Transform::setLocationZ(float loc) {
    if(loc != locationZ) {
        locationZ = loc;
        inverseMatrixCalculated = false;
        matrixCalculated = false;
    }
}

void Transform::setRotationX(float rotInDeg) {
    if(rotInDeg != rotationX) {
        rotationX = rotInDeg;
        inverseMatrixCalculated = false;
        matrixCalculated = false;
    }
}

void Transform::setRotationY(float rotInDeg) {
    if(rotInDeg != rotationY) {
        rotationY = rotInDeg;
        inverseMatrixCalculated = false;
        matrixCalculated = false;
    }
}

void Transform::setRotationZ(float rotInDeg) {
    if(rotInDeg != rotationZ) {
        rotationZ = rotInDeg;
        inverseMatrixCalculated = false;
        matrixCalculated = false;
    }
}

void Transform::setScaleX(float scale) {
    if(scale != scaleX) {
        scaleX = scale;
        inverseMatrixCalculated = false;
        matrixCalculated = false;
    }
}

void Transform::setScaleY(float scale) {
    if(scale != scaleY) {
        scaleY = scale;
        inverseMatrixCalculated = false;
        matrixCalculated = false;
    }
}

void Transform::setScaleZ(float scale) {
    if(scale != scaleZ) {
        scaleZ = scale;
        inverseMatrixCalculated = false;
        matrixCalculated = false;
    }
}

void Transform::setUniformScale(float scale) {
    scaleX = scaleY = scaleZ = scale;
    inverseMatrixCalculated = false;
    matrixCalculated = false;
}

Matrix4 Transform::getAsMatrix4() {
    // Assume fixed coordinate system, so the order is Scale -> Rotation -> Location (note that Matrix multiplication is evaluated from right to left)

    if(matrixCalculated) {
        return matrix;
    }

    matrix = Matrix4::identity();

    if(locationX != 0.0 || locationY != 0.0 || locationZ != 0.0) {
        matrix = matrix * Matrix4::translation(locationX, locationY, locationZ);
    }

    if(rotationZ != 0.0) {
        matrix = matrix * Matrix4::rotationZ(rotationZ);
    }

    if(rotationY != 0.0) {
        matrix = matrix * Matrix4::rotationY(rotationY);
    }

    if(rotationX != 0.0) {
        matrix = matrix * Matrix4::rotationX(rotationX);
    }

    if(scaleX != 1.0 || scaleY != 1.0 || scaleZ != 1.0) {
        matrix = matrix * Matrix4::scale(scaleX, scaleY, scaleZ);
    }

    matrixCalculated = true;

    return matrix;
}

Matrix4 Transform::getInverseAsMatrix4() {
    // Inverse also reverses the order

    if(inverseMatrixCalculated) {
        return inverseMatrix;
    }

    inverseMatrix = Matrix4::identity();

    if(scaleX != 1.0 || scaleY != 1.0 || scaleZ != 1.0) {
        inverseMatrix = inverseMatrix * Matrix4::scale(1.0 / scaleX, 1.0 / scaleY, 1.0 / scaleZ);
    }

    if(rotationX != 0.0) {
        inverseMatrix = inverseMatrix * Matrix4::rotationX(-rotationX);
    }

    if(rotationY != 0.0) {
        inverseMatrix = inverseMatrix * Matrix4::rotationY(-rotationY);
    }

    if(rotationZ != 0.0) {
        inverseMatrix = inverseMatrix * Matrix4::rotationZ(-rotationZ);
    }

    if(locationX != 0.0 || locationY != 0.0 || locationZ != 0.0) {
        inverseMatrix = inverseMatrix * Matrix4::translation(-locationX, -locationY, -locationZ);
    }

    inverseMatrixCalculated = true;

    return inverseMatrix;
}