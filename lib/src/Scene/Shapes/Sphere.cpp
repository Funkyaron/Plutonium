

#include <math.h>


#include "Shape.h"
#include "Ray.h"



bool Sphere::hit(Ray r, float t0, float t1, HitRecord& rec) const {
    Vector3 oc = r.getOrigin();
    float a = dot(r.getDirection(), r.getDirection());
    float b = dot(oc, r.getDirection());
    float c = dot(oc, oc) - 1.0;
    float discriminant = b * b -  a * c;
    if(discriminant > 0) {
        float temp = (-b - sqrt(b * b - a * c)) / a;
        if(temp < t1 && temp > t0) {
            rec.t = temp;
            rec.p = r.pointAtParameter(temp);
            rec.normal = rec.p;
            return true;
        }
        temp = (-b + sqrt(b * b - a * c)) / a;
        if(temp < t1 && temp > t0) {
            rec.t = temp;
            rec.p = r.pointAtParameter(temp);
            rec.normal = rec.p;
            return true;
        }
    }
    return false;
}
