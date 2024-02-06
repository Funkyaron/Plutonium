


#include "ProbabilityDensityFunction.h"
#include "Utility.h"

#include <limits>
#include <math.h>



void BoxProbabilityDensityFunction::setOrigin(const Vector3& origin_) {
    origin = origin_;
}

float BoxProbabilityDensityFunction::value(const Vector3& direction) const {
    float t0 = 0.001;
    float t1 = std::numeric_limits<float>::max();
    if(bbox.hit(Ray(origin, direction), t0, t1)) {
        float rectSum = 0.0;
        rectSum += xminValue(origin, direction, t0, t1);
        rectSum += xmaxValue(origin, direction, t0, t1);
        rectSum += yminValue(origin, direction, t0, t1);
        rectSum += ymaxValue(origin, direction, t0, t1);
        rectSum += zminValue(origin, direction, t0, t1);
        rectSum += zmaxValue(origin, direction, t0, t1);
        return rectSum / 6.0;
    }
    else {
        return 0.0;
    }
}

Vector3 BoxProbabilityDensityFunction::generate() const {

    float x0 = bbox.getxmin();
    float x1 = bbox.getxmax();
    float y0 = bbox.getymin();
    float y1 = bbox.getymax();
    float z0 = bbox.getzmin();
    float z1 = bbox.getzmax();

    Vector3 randomPoint;

    float rectDecide = Plutonium::getRandomNumber() * 6.0;
    if(rectDecide < 1.0) {
        // randomPoint on xmin plane
        randomPoint = Vector3(x0, y0 + Plutonium::getRandomNumber() * (y1 - y0), z0 + Plutonium::getRandomNumber() * (z1 - z0));
    }
    else if(rectDecide < 2.0) {
        // random point on xmax plane
        randomPoint = Vector3(x1, y0 + Plutonium::getRandomNumber() * (y1 - y0), z0 + Plutonium::getRandomNumber() * (z1 - z0));
    }
    else if(rectDecide < 3.0) {
        // random point on ymin plane
        randomPoint = Vector3(x0 + Plutonium::getRandomNumber() * (x1 - x0), y0, z0 + Plutonium::getRandomNumber() * (z1 - z0));
    }
    else if(rectDecide < 4.0) {
        // random point on ymax plane
        randomPoint = Vector3(x0 + Plutonium::getRandomNumber() * (x1 - x0), y1, z0 + Plutonium::getRandomNumber() * (z1 - z0));
    }
    else if(rectDecide < 5.0) {
        // random point on zmin plane
        randomPoint = Vector3(x0 + Plutonium::getRandomNumber() * (x1 - x0), y0 + Plutonium::getRandomNumber() * (y1 - y0), z0);
    }
    else {
        // random point on zmax plane
        randomPoint = Vector3(x0 + Plutonium::getRandomNumber() * (x1 - x0), y0 + Plutonium::getRandomNumber() * (y1 - y0), z1);
    }

    return randomPoint - origin;
}






float BoxProbabilityDensityFunction::xminValue(const Vector3& origin, const Vector3& direction, float t0, float t1) const {
    float t = (bbox.getxmin() - origin.x()) / direction.x();
    if(t < t0 || t > t1) {
        return 0.0;
    }
    float y = origin.y() + t * direction.y();
    float z = origin.z() + t * direction.z();
    if(y < bbox.getymin() || y > bbox.getymax() || z < bbox.getzmin() || z > bbox.getzmax()) {
        return 0.0;
    }
    float area = (bbox.getymax() - bbox.getymin()) * (bbox.getzmax() - bbox.getzmin());
    float distanceSquared = t * t * direction.squaredLength();
    float cosine = fabs(direction.x() / direction.length());
    return distanceSquared / (cosine * area);
}

float BoxProbabilityDensityFunction::xmaxValue(const Vector3& origin, const Vector3& direction, float t0, float t1) const {
    float t = (bbox.getxmax() - origin.x()) / direction.x();
    if(t < t0 || t > t1) {
        return 0.0;
    }
    float y = origin.y() + t * direction.y();
    float z = origin.z() + t * direction.z();
    if(y < bbox.getymin() || y > bbox.getymax() || z < bbox.getzmin() || z > bbox.getzmax()) {
        return 0.0;
    }
    float area = (bbox.getymax() - bbox.getymin()) * (bbox.getzmax() - bbox.getzmin());
    float distanceSquared = t * t * direction.squaredLength();
    float cosine = fabs(direction.x() / direction.length());
    return distanceSquared / (cosine * area);
}

float BoxProbabilityDensityFunction::yminValue(const Vector3& origin, const Vector3& direction, float t0, float t1) const {
    float t = (bbox.getymin() - origin.y()) / direction.y();
    if(t < t0 || t > t1) {
        return 0.0;
    }
    float x = origin.x() + t * direction.x();
    float z = origin.z() + t * direction.z();
    if(x < bbox.getxmin() || x > bbox.getxmax() || z < bbox.getzmin() || z > bbox.getzmax()) {
        return 0.0;
    }
    float area = (bbox.getxmax() - bbox.getxmin()) * (bbox.getzmax() - bbox.getzmin());
    float distanceSquared = t * t * direction.squaredLength();
    float cosine = fabs(direction.y() / direction.length());
    return distanceSquared / (cosine * area);
}

float BoxProbabilityDensityFunction::ymaxValue(const Vector3& origin, const Vector3& direction, float t0, float t1) const {
    float t = (bbox.getymax() - origin.y()) / direction.y();
    if(t < t0 || t > t1) {
        return 0.0;
    }
    float x = origin.x() + t * direction.x();
    float z = origin.z() + t * direction.z();
    if(x < bbox.getxmin() || x > bbox.getxmax() || z < bbox.getzmin() || z > bbox.getzmax()) {
        return 0.0;
    }
    float area = (bbox.getxmax() - bbox.getxmin()) * (bbox.getzmax() - bbox.getzmin());
    float distanceSquared = t * t * direction.squaredLength();
    float cosine = fabs(direction.y() / direction.length());
    return distanceSquared / (cosine * area);
}

float BoxProbabilityDensityFunction::zminValue(const Vector3& origin, const Vector3& direction, float t0, float t1) const {
    float t = (bbox.getzmin() - origin.z()) / direction.z();
    if(t < t0 || t > t1) {
        return 0.0;
    }
    float x = origin.x() + t * direction.x();
    float y = origin.y() + t * direction.y();
    if(x < bbox.getxmin() || x > bbox.getxmax() || y < bbox.getymin() || y > bbox.getymax()) {
        return 0.0;
    }
    float area = (bbox.getxmax() - bbox.getxmin()) * (bbox.getymax() - bbox.getymin());
    float distanceSquared = t * t * direction.squaredLength();
    float cosine = fabs(direction.z() / direction.length());
    return distanceSquared / (cosine * area);
}

float BoxProbabilityDensityFunction::zmaxValue(const Vector3& origin, const Vector3& direction, float t0, float t1) const {
    float t = (bbox.getzmax() - origin.z()) / direction.z();
    if(t < t0 || t > t1) {
        return 0.0;
    }
    float x = origin.x() + t * direction.x();
    float y = origin.y() + t * direction.y();
    if(x < bbox.getxmin() || x > bbox.getxmax() || y < bbox.getymin() || y > bbox.getymax()) {
        return 0.0;
    }
    float area = (bbox.getxmax() - bbox.getxmin()) * (bbox.getymax() - bbox.getymin());
    float distanceSquared = t * t * direction.squaredLength();
    float cosine = fabs(direction.z() / direction.length());
    return distanceSquared / (cosine * area);
}
