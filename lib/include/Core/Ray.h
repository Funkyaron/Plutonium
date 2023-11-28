



#ifndef PLUTONIUM_RAY_H
#define PLUTONIUM_RAY_H



#include "Vector3.h"
#include "Vector4.h"


class Matrix4;


class Ray {
public:

    Ray();
    Ray(const Vector3& origin_, const Vector3& direction_);
    Ray(const Vector4& origin_, const Vector4& direction_);

    Vector3 getOrigin() const;
    void setOrigin(const Vector3& newOrigin);
    void setOrigin(const Vector4& newOrigin);

    Vector3 getDirection() const;
    void setDirection(const Vector3& newDirection);
    void setDirection(const Vector4& newDirection);

    Vector3 pointAtParameter(float t) const;

    Ray getTransformedRay(const Matrix4& m);

private:

    Vector4 origin;
    Vector4 direction;

};





#endif