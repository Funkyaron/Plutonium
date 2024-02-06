




#include "Shape.h"
#include "Matrix4.h"
#include "Ray.h"
#include "Transform.h"
#include "Material.h"


#include <array>
#include <limits>




ShapeInstance::ShapeInstance() {
    shape = nullptr;
    transform = std::make_shared<Transform>();
    material = nullptr;
}

ShapeInstance::ShapeInstance(std::shared_ptr<Shape> shape_, std::shared_ptr<Transform> transform_, std::shared_ptr<Material> material_) {
    shape = shape_;
    transform = transform_;
    material = material_;
}




bool ShapeInstance::hit(Ray r, float t0, float t1, HitRecord& rec) const {

    Matrix4 inverse = transform->getInverseAsMatrix4();

    Ray transfomedRay = r.getTransformedRay(inverse);

    if(shape->hit(transfomedRay, t0, t1, rec)) {
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


BoundingBox ShapeInstance::createBoundingBox() {
    BoundingBox originalBoundingBox = shape->createBoundingBox();

    std::array<Vector4, 8> corners = {

        Vector4(originalBoundingBox.getxmin(), originalBoundingBox.getymin(), originalBoundingBox.getzmin(), 1.0),
        Vector4(originalBoundingBox.getxmin(), originalBoundingBox.getymin(), originalBoundingBox.getzmax(), 1.0),
        Vector4(originalBoundingBox.getxmin(), originalBoundingBox.getymax(), originalBoundingBox.getzmin(), 1.0),
        Vector4(originalBoundingBox.getxmin(), originalBoundingBox.getymax(), originalBoundingBox.getzmax(), 1.0),
        Vector4(originalBoundingBox.getxmax(), originalBoundingBox.getymin(), originalBoundingBox.getzmin(), 1.0),
        Vector4(originalBoundingBox.getxmax(), originalBoundingBox.getymin(), originalBoundingBox.getzmax(), 1.0),
        Vector4(originalBoundingBox.getxmax(), originalBoundingBox.getymax(), originalBoundingBox.getzmin(), 1.0),
        Vector4(originalBoundingBox.getxmax(), originalBoundingBox.getymax(), originalBoundingBox.getzmax(), 1.0)

    };

    Matrix4 transformMatrix = transform->getAsMatrix4();

    corners[0] = transformMatrix * corners[0];
    corners[1] = transformMatrix * corners[1];
    corners[2] = transformMatrix * corners[2];
    corners[3] = transformMatrix * corners[3];
    corners[4] = transformMatrix * corners[4];
    corners[5] = transformMatrix * corners[5];
    corners[6] = transformMatrix * corners[6];
    corners[7] = transformMatrix * corners[7];

    float xmin = std::numeric_limits<float>::max();
    float xmax = std::numeric_limits<float>::lowest();
    float ymin = std::numeric_limits<float>::max();
    float ymax = std::numeric_limits<float>::lowest();
    float zmin = std::numeric_limits<float>::max();
    float zmax = std::numeric_limits<float>::lowest();

    for(int i = 0; i < 8; i++) {
        if(corners[i].x() < xmin) {
            xmin = corners[i].x();
        }
        if(corners[i].x() > xmax) {
            xmax = corners[i].x();
        }
        if(corners[i].y() < ymin) {
            ymin = corners[i].y();
        }
        if(corners[i].y() > ymax) {
            ymax = corners[i].y();
        }
        if(corners[i].z() < zmin) {
            zmin = corners[i].z();
        }
        if(corners[i].z() > zmax) {
            zmax = corners[i].z();
        }
    }

    return BoundingBox(xmin, xmax, ymin, ymax, zmin, zmax);
}


Vector4 ShapeInstance::getCenter() {
    return transform->getAsMatrix4() * shape->getCenter();
}


std::shared_ptr<Shape> ShapeInstance::buildBVH(int axis, std::vector<BoundingBox>& importantBoxes, std::function<bool(std::shared_ptr<ShapeInstance>)> ruleset) {
    shape = shape->buildBVH(axis, importantBoxes, ruleset);
    if(ruleset(std::dynamic_pointer_cast<ShapeInstance>(shared_from_this())) == true) {
        importantBoxes.push_back(this->createBoundingBox());
    }
    return shared_from_this();
}





void ShapeInstance::setShape(std::shared_ptr<Shape> shape_) {
    shape = shape_;
}

std::shared_ptr<Shape> ShapeInstance::getShape() const {
    return shape;
}

void ShapeInstance::setTransform(std::shared_ptr<Transform> transform_) {
    transform = transform_;
}

std::shared_ptr<Transform> ShapeInstance::getTransform() const {
    return transform;
}

void ShapeInstance::setMaterial(std::shared_ptr<Material> material_) {
    material = material_;
}

std::shared_ptr<Material> ShapeInstance::getMaterial() const {
    return material;
}