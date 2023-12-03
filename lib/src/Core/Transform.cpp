



#include "Transform.h"
#include "Matrix4.h"



Transform::Transform() {
    locationX = locationY = locationZ = 0.0;
    rotationX = rotationY = rotationZ = 0.0;
    scaleX = scaleY = scaleZ = 1.0;

    calculateMatrix();
    calculateInverseMatrix();
}

void Transform::setLocationX(float loc) {
    if(loc != locationX) {
        locationX = loc;
        calculateMatrix();
        calculateInverseMatrix();
    }
}

void Transform::setLocationY(float loc) {
    if(loc != locationY) {
        locationY = loc;
        calculateMatrix();
        calculateInverseMatrix();
    }
}

void Transform::setLocationZ(float loc) {
    if(loc != locationZ) {
        locationZ = loc;
        calculateMatrix();
        calculateInverseMatrix();
    }
}

void Transform::setRotationX(float rotInDeg) {
    if(rotInDeg != rotationX) {
        rotationX = rotInDeg;
        calculateMatrix();
        calculateInverseMatrix();
    }
}

void Transform::setRotationY(float rotInDeg) {
    if(rotInDeg != rotationY) {
        rotationY = rotInDeg;
        calculateMatrix();
        calculateInverseMatrix();
    }
}

void Transform::setRotationZ(float rotInDeg) {
    if(rotInDeg != rotationZ) {
        rotationZ = rotInDeg;
        calculateMatrix();
        calculateInverseMatrix();
    }
}

void Transform::setScaleX(float scale) {
    if(scale != scaleX) {
        scaleX = scale;
        calculateMatrix();
        calculateInverseMatrix();
    }
}

void Transform::setScaleY(float scale) {
    if(scale != scaleY) {
        scaleY = scale;
        calculateMatrix();
        calculateInverseMatrix();
    }
}

void Transform::setScaleZ(float scale) {
    if(scale != scaleZ) {
        scaleZ = scale;
        calculateMatrix();
        calculateInverseMatrix();
    }
}

void Transform::setUniformScale(float scale) {
    scaleX = scaleY = scaleZ = scale;
    calculateMatrix();
    calculateInverseMatrix();
}

Matrix4 Transform::getAsMatrix4() const {
    return matrix;
}

Matrix4 Transform::getInverseAsMatrix4() const {
    return inverseMatrix;
}


void Transform::calculateMatrix() {

    // Assume fixed coordinate system, so the order is Scale -> Rotation -> Location (note that Matrix multiplication is evaluated from right to left)
    
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

}

void Transform::calculateInverseMatrix() {

    // Inverse also reverses the order

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

}