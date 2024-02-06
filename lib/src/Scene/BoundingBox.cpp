




#include "BoundingBox.h"
#include "Ray.h"
#include "Vector3.h"

#include <algorithm>



BoundingBox::BoundingBox(float xmin_, float xmax_, float ymin_, float ymax_, float zmin_, float zmax_) {
    xmin = xmin_;
    xmax = xmax_;
    ymin = ymin_;
    ymax = ymax_;
    zmin = zmin_;
    zmax = zmax_;
}

BoundingBox::BoundingBox(const BoundingBox& bbox1, const BoundingBox& bbox2) {
    if(bbox1.getxmin() < bbox2.getxmin()) {
        xmin = bbox1.getxmin();
    }
    else {
        xmin = bbox2.getxmin();
    }
    if(bbox1.getxmax() > bbox2.getxmax()) {
        xmax = bbox1.getxmax();
    }
    else {
        xmax = bbox2.getxmax();
    }
    if(bbox1.getymin() < bbox2.getymin()) {
        ymin = bbox1.getymin();
    }
    else {
        ymin = bbox2.getymin();
    }
    if(bbox1.getymax() > bbox2.getymax()) {
        ymax = bbox1.getymax();
    }
    else {
        ymax = bbox2.getymax();
    }
    if(bbox1.getzmin() < bbox2.getzmin()) {
        zmin = bbox1.getzmin();
    }
    else {
        zmin = bbox2.getzmin();
    }
    if(bbox1.getzmax() > bbox2.getzmax()) {
        zmax = bbox1.getzmax();
    }
    else {
        zmax = bbox2.getzmax();
    }
}




bool BoundingBox::hit(Ray r, float t0, float t1) const {
    Vector3 origin = r.getOrigin();
    Vector3 direction = r.getDirection();

    float t_xmin, t_xmax, t_ymin, t_ymax, t_zmin, t_zmax;

    float a = 1.0 / direction.x();
    if(a >= 0) {
        t_xmin = a * (xmin - origin.x());
        t_xmax = a * (xmax - origin.x());
    }
    else {
        t_xmin = a * (xmax - origin.x());
        t_xmax = a * (xmin - origin.x());
    }

    a = 1.0 / direction.y();
    if(a >= 0) {
        t_ymin = a * (ymin - origin.y());
        t_ymax = a * (ymax - origin.y());
    }
    else {
        t_ymin = a * (ymax - origin.y());
        t_ymax = a * (ymin - origin.y());
    }

    a = 1.0 / direction.z();
    if(a >= 0) {
        t_zmin = a * (zmin - origin.z());
        t_zmax = a * (zmax - origin.z());
    }
    else {
        t_zmin = a * (zmax - origin.z());
        t_zmax = a * (zmin - origin.z());
    }

    t_xmin = std::max(t_xmin, t0);
    t_xmax = std::min(t_xmax, t1);
    t_ymin = std::max(t_ymin, t0);
    t_ymax = std::min(t_ymax, t1);
    t_zmin = std::max(t_zmin, t0);
    t_zmax = std::min(t_zmax, t1);

    if(t_xmin < t_ymax
        && t_xmin < t_zmax
        && t_ymin < t_xmax
        && t_ymin < t_zmax
        && t_zmin < t_xmax
        && t_zmin < t_ymax)
    {
        return true;
    }
    else
    {
        return false;
    }
}



// bool BoundingBox::hit(Ray r, float t0, float t1, HitRecord hrec) {
//     Vector3 origin = r.getOrigin();
//     Vector3 direction = r.getDirection();

//     float t_xmin, t_xmax, t_ymin, t_ymax, t_zmin, t_zmax;

//     float ax = 1.0 / direction.x();
//     if(ax >= 0.0) {
//         t_xmin = ax * (xmin - origin.x());
//         t_xmax = ax * (xmax - origin.x());
//     }
//     else {
//         t_xmin = ax * (xmax - origin.x());
//         t_xmax = ax * (xmin - origin.x());
//     }

//     float ay = 1.0 / direction.y();
//     if(ay >= 0.0) {
//         t_ymin = ay * (ymin - origin.y());
//         t_ymax = ay * (ymax - origin.y());
//     }
//     else {
//         t_ymin = ay * (ymax - origin.y());
//         t_ymax = ay * (ymin - origin.y());
//     }

//     float az = 1.0 / direction.z();
//     if(az >= 0.0) {
//         t_zmin = az * (zmin - origin.z());
//         t_zmax = az * (zmax - origin.z());
//     }
//     else {
//         t_zmin = az * (zmax - origin.z());
//         t_zmax = az * (zmin - origin.z());
//     }

//     float t_xmin_clamped = std::max(t_xmin, t0);
//     float t_xmax_clamped = std::min(t_xmax, t1);
//     float t_ymin_clamped = std::max(t_ymin, t0);
//     float t_ymax_clamped = std::min(t_ymax, t1);
//     float t_zmin_clamped = std::max(t_zmin, t0);
//     float t_zmax_clamped = std::min(t_zmax, t1);

//     if(t_xmin_clamped < t_ymax_clamped
//         && t_xmin_clamped < t_zmax_clamped
//         && t_ymin_clamped < t_xmax_clamped
//         && t_ymin_clamped < t_zmax_clamped
//         && t_zmin_clamped < t_xmax_clamped
//         && t_zmin_clamped < t_ymax_clamped)
//     {
//         hrec.t = std::numeric_limits<float>::infinity();
//         if(t_xmin > t0 && t_xmin < t1 && t_xmin < hrec.t) {
//             hrec.t = t_xmin;
//             hrec.p = r.pointAtParameter(hrec.t);
//             if(ax >= 0.0) {
//                 // t_xmin -> xmin
//                 hrec.normal = Vector3(-1.0, 0.0, 0.0);
//             }
//             else {
//                 // t_xmin -> xmax
//                 hrec.normal = Vector3(1.0, 0.0, 0.0);
//             }
//         }
//         if(t_xmax > t0 && t_xmax < t1 && t_xmax < hrec.t) {
//             hrec.t = t_xmax;
//             hrec.p = r.pointAtParameter(hrec.t);
//             if(ax >= 0.0) {
//                 // t_xmax -> xmax
//                 hrec.normal = Vector3(1.0, 0.0, 0.0);
//             }
//             else {
//                 // t_xmax -> xmin
//                 hrec.normal = Vector3(-1.0, 0.0, 0.0);
//             }
//         }
//         if(t_ymin > t0 && t_ymin < t1 && t_ymin < hrec.t) {
//             hrec.t = t_ymin;
//             hrec.p = r.pointAtParameter(hrec.t);
//             if(ay >= 0.0) {
//                 // t_ymin -> ymin
//                 hrec.normal = Vector3(0.0, -1.0, 0.0);
//             }
//             else {
//                 // t_ymin -> ymax
//                 hrec.normal = Vector3(0.0, 1.0, 0.0);
//             }
//         }
//         if(t_ymax > t0 && t_ymax < t1 && t_ymax < hrec.t) {
//             hrec.t = t_ymax;
//             hrec.p = r.pointAtParameter(hrec.t);
//             if(ay >= 0.0) {
//                 // t_ymax -> ymax
//                 hrec.normal = Vector3(0.0, 1.0, 0.0);
//             }
//             else {
//                 // t_ymax -> ymin
//                 hrec.normal = Vector3(0.0, -1.0, 0.0);
//             }
//         }
//         if(t_zmin > t0 && t_zmin < t1 && t_zmin < hrec.t) {
//             hrec.t = t_zmin;
//             hrec.p = r.pointAtParameter(hrec.t);
//             if(az >= 0.0) {
//                 // t_zmin -> zmin
//                 hrec.normal = Vector3(0.0, 0.0, -1.0);
//             }
//             else {
//                 // t_zmin -> zmax
//                 hrec.normal = Vector3(0.0, 0.0, 1.0);
//             }
//         }
//         if(t_zmax > t0 && t_zmax < t1 && t_zmax < hrec.t) {
//             hrec.t = t_zmax;
//             hrec.p = r.pointAtParameter(hrec.t);
//             if(az >= 0.0) {
//                 // t_zmax -> zmax
//                 hrec.normal = Vector3(0.0, 0.0, 1.0);
//             }
//             else {
//                 // t_zmax -> zmin
//                 hrec.normal = Vector3(0.0, 0.0, -1.0);
//             }
//         }
//         hrec.material = nullptr;
//         return true;
//     }
//     else
//     {
//         return false;
//     }
// }





float BoundingBox::getxmin() const {
    return xmin;
}

float BoundingBox::getxmax() const {
    return xmax;
}

float BoundingBox::getymin() const {
    return ymin;
}

float BoundingBox::getymax() const {
    return ymax;
}

float BoundingBox::getzmin() const {
    return zmin;
}

float BoundingBox::getzmax() const {
    return zmax;
}
