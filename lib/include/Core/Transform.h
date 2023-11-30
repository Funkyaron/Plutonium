



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

    Matrix4 getAsMatrix4();
    Matrix4 getInverseAsMatrix4();

private:

    float locationX, locationY, locationZ;
    float rotationX, rotationY, rotationZ; // We only support rotation mode XYZ Euler for now
    float scaleX, scaleY, scaleZ;

    Matrix4 inverseMatrix;
    Matrix4 matrix;

    bool inverseMatrixCalculated;
    bool matrixCalculated;

};





#endif