

#include "Ray.h"
#include "Matrix4.h"



Ray::Ray() {}

Ray::Ray(const Vector3& origin_, const Vector3& direction_) {
    origin = Vector4::position(origin_);
    direction = Vector4::direction(direction_);
}

Ray::Ray(const Vector4& origin_, const Vector4& direction_) {
    origin = origin_;
    direction = direction_;
}

Vector3 Ray::getOrigin() const {
    return Vector3(origin.x(), origin.y(), origin.z());
}

void Ray::setOrigin(const Vector3& newOrigin) {
    origin = Vector4::position(newOrigin);
}

void Ray::setOrigin(const Vector4& newOrigin) {
    origin = newOrigin;
}

Vector3 Ray::getDirection() const {
    return Vector3(direction.x(), direction.y(), direction.z());
}

void Ray::setDirection(const Vector3& newDirection) {
    direction = Vector4::direction(newDirection);
}

void Ray::setDirection(const Vector4& newDirection) {
    direction = newDirection;
}

Vector3 Ray::pointAtParameter(float t) const {
    Vector4 point = origin + t * direction;
    return Vector3(point.x(), point.y(), point.z());
}

Ray Ray::getTransformedRay(const Matrix4& m) {
    return Ray(m * origin, m * direction);
}