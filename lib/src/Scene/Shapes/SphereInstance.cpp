



#include "Shape.h"
#include "Material.h"
#include "Matrix3.h"
#include "Matrix4.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Ray.h"



SphereInstance::SphereInstance() {

    transformMatrix = Matrix4::scale(0.5, 1.0, 1.0) * Matrix4::rotationZ(-45.0) * Matrix4::translation(-2.0, 0.0, 0.0);

    mSphere = std::make_shared<Sphere>(Vector3(0.0, 0.0, 0.0), 1.0, std::make_shared<Metal>(Color(0.8, 0.8, 0.8), 0.1));
}

bool SphereInstance::hit(Ray r, float t0, float t1, HitRecord& rec) const {
    Vector3 originalOrigin = r.getOrigin();
    Vector3 originalDirection = r.getDirection();

    Ray transfomedRay(transformMatrix * Vector4::position(originalOrigin), transformMatrix * Vector4::direction(originalDirection));

    if(mSphere->hit(transfomedRay, t0, t1, rec)) {
        rec.p = r.pointAtParameter(rec.t);
        rec.normal = unitVector(transformMatrix.getTranspose() * Vector4::direction(rec.normal));
        return true;
    }
    else {
        return false;
    }

}