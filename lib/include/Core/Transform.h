



#ifndef PLUTONIUM_TRANSFORM_H
#define PLUTONIUM_TRANSFORM_H


#include "Matrix4.h"


class Transform {
public:

    Transform();

    void setLocationX(float loc);
    void setLocationY(float loc);
    void setLocationZ(float loc);

    void setRotationX(float rotInDeg);
    void setRotationY(float rotInDeg);
    void setRotationZ(float rotInDeg);

    void setScaleX(float scale);
    void setScaleY(float scale);
    void setScaleZ(float scale);
    void setUniformScale(float scale);

    Matrix4 getAsMatrix4() const;
    Matrix4 getInverseAsMatrix4() const;

private:

    float locationX, locationY, locationZ;
    float rotationX, rotationY, rotationZ; // We only support rotation mode XYZ Euler for now
    float scaleX, scaleY, scaleZ;

    Matrix4 matrix;
    Matrix4 inverseMatrix;

    void calculateMatrix();
    void calculateInverseMatrix();

};





#endif