

#include "Ray.h"




Ray::Ray() {}

Ray::Ray(const Vector3& origin_, const Vector3& direction_) {
    origin = origin_;
    direction = direction_;
}

Vector3 Ray::getOrigin() const {
    return origin;
}

void Ray::setOrigin(Vector3& newOrigin) {
    origin = newOrigin;
}

Vector3 Ray::getDirection() const {
    return direction;
}
void Ray::setDirection(Vector3& newDirection) {
    direction = newDirection;
}

Vector3 Ray::pointAtParameter(float t) const {
    return origin + t * direction;
}