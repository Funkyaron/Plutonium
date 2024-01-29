


#include <limits>


#include "Shape.h"
#include "Ray.h"



// I imagine a rectangle lying on the xz plane, facing up, measuring -1.0 to 1.0 in the x and z direction
// => Hit function first checks y = 0

bool Rectangle::hit(Ray r, float t0, float t1, HitRecord& rec) const {
    
    float a = 1.0 / r.getDirection().y();
    float t = a * (-r.getOrigin().y());

    if(t < t0 || t > t1) {
        return false;
    }

    Vector3 point = r.pointAtParameter(t);

    if(point.x() < -1.0 || point.x() > 1.0 || point.z() < -1.0 || point.z() > 1.0) {
        return false;
    }

    rec.t = t;
    rec.p = point;
    rec.normal = Vector3(0.0, 1.0, 0.0);

    return true;
}

BoundingBox Rectangle::createBoundingBox() {
    return BoundingBox(-1.0, 1.0, -std::numeric_limits<float>::epsilon(), std::numeric_limits<float>::epsilon(), -1.0, 1.0);
}

Vector4 Rectangle::getCenter() {
    return Vector4(0.0, 0.0, 0.0, 1.0);
}