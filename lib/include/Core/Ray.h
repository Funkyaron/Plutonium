



#ifndef PLUTONIUM_RAY_H
#define PLUTONIUM_RAY_H



#include "Vector3.h"



class Ray {
public:

    Ray();
    Ray(const Vector3& origin_, const Vector3& direction_);

    Vector3 getOrigin() const;
    void setOrigin(Vector3& newOrigin);

    Vector3 getDirection() const;
    void setDirection(Vector3& newDirection);

    Vector3 pointAtParameter(float t) const;

private:

    Vector3 origin;
    Vector3 direction;

};





#endif