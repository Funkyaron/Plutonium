




#include "Shape.h"
#include "Matrix4.h"
#include "Ray.h"
#include "Transform.h"
#include "Material.h"





GeometryInstance::GeometryInstance() {
    geometry = nullptr;
    transform = std::make_shared<Transform>();
    material = nullptr;
}

GeometryInstance::GeometryInstance(std::shared_ptr<Geometry> geometry_, std::shared_ptr<Transform> transform_, std::shared_ptr<Material> material_) {
    geometry = geometry_;
    transform = transform_;
    material = material_;
}




bool GeometryInstance::hit(Ray r, float t0, float t1, HitRecord& rec) const {

    Matrix4 inverse = transform->getInverseAsMatrix4();

    Ray transfomedRay = r.getTransformedRay(inverse);

    if(geometry->hit(transfomedRay, t0, t1, rec)) {
        rec.p = r.pointAtParameter(rec.t);
        inverse.transpose();
        Vector4 transformedNormal = inverse * Vector4::direction(rec.normal);
        rec.normal = unitVector(Vector3(transformedNormal.x(), transformedNormal.y(), transformedNormal.z()));
        rec.material = material;
        return true;
    }
    else {
        return false;
    }

}





void GeometryInstance::setGeometry(std::shared_ptr<Geometry> geometry_) {
    geometry = geometry_;
}

std::shared_ptr<Geometry> GeometryInstance::getGeometry() const {
    return geometry;
}

void GeometryInstance::setTransform(std::shared_ptr<Transform> transform_) {
    transform = transform_;
}

std::shared_ptr<Transform> GeometryInstance::getTransform() const {
    return transform;
}

void GeometryInstance::setMaterial(std::shared_ptr<Material> material_) {
    material = material_;
}

std::shared_ptr<Material> GeometryInstance::getMaterial() const {
    return material;
}