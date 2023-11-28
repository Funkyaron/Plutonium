



#include "Transform.h"
#include "Matrix4.h"



Transform::Transform() {
    locationX = locationY = locationZ = 0.0;
    rotationX = rotationY = rotationZ = 0.0;
    scaleX = scaleY = scaleZ = 1.0;
}

void Transform::setLocationX(float loc) {
    locationX = loc;
}

void Transform::setLocationY(float loc) {
    locationY = loc;
}

void Transform::setLocationZ(float loc) {
    locationZ = loc;
}

void Transform::setRotationX(float rotInDeg) {
    rotationX = rotInDeg;
}

void Transform::setRotationY(float rotInDeg) {
    rotationY = rotInDeg;
}

void Transform::setRotationZ(float rotInDeg) {
    rotationZ = rotInDeg;
}

void Transform::setScaleX(float scale) {
    scaleX = scale;
}

void Transform::setScaleY(float scale) {
    scaleY = scale;
}

void Transform::setScaleZ(float scale) {
    scaleZ = scale;
}

void Transform::setUniformScale(float scale) {
    scaleX = scaleY = scaleZ = scale;
}

Matrix4 Transform::getAsMatrix4() {
    // Assume fixed coordinate system, so the order is Scale -> Rotation -> Location (note that Matrix multiplication is evaluated from right to left)

    return Matrix4::translation(locationX, locationY, locationZ)
        * Matrix4::rotationZ(rotationZ)
        * Matrix4::rotationY(rotationY)
        * Matrix4::rotationX(rotationX)
        * Matrix4::scale(scaleX, scaleY, scaleZ);
}

Matrix4 Transform::getInverseAsMatrix4() {
    // Inverse also reverses the order

    return Matrix4::scale(1.0 / scaleX, 1.0 / scaleY, 1.0 / scaleZ)
        * Matrix4::rotationX(-rotationX)
        * Matrix4::rotationY(-rotationY)
        * Matrix4::rotationZ(-rotationZ)
        * Matrix4::translation(-locationX, -locationY, -locationZ);
}