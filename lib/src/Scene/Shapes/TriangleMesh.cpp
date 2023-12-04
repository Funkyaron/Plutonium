


#include "Shape.h"
#include "Ray.h"


bool TriangleMesh::hitTriangle(Ray r, float t0, float t1, HitRecord& rec, const Vector4& p1, const Vector4& p2, const Vector4& p3) const {
    float a = p1.x() - p2.x();
    float b = p1.y() - p2.y();
    float c = p1.z() - p2.z();
    float d = p1.x() - p3.x();
    float e = p1.y() - p3.y();
    float f = p1.z() - p3.z();
    float g = r.getDirection().x();
    float h = r.getDirection().y();
    float i = r.getDirection().z();
    float j = p1.x() - r.getOrigin().x();
    float k = p1.y() - r.getOrigin().y();
    float l = p1.z() - r.getOrigin().z();

    float ei_hf = e * i - h * f;
    float gf_di = g * f - d * i;
    float dh_eg = d * h - e * g;
    float ak_jb = a * k - j * b;
    float jc_al = j * c - a * l;
    float bl_kc = b * l - k * c;

    float M = a * ei_hf + b * gf_di + c * dh_eg;

    float t = - (f * ak_jb + e * jc_al + d * bl_kc) / M;
    if(t < t0 || t > t1) {
        return false;
    }

    float gamma = (i * ak_jb + h * jc_al + g * bl_kc) / M;
    if(gamma < 0 || gamma > 1) {
        return false;
    }

    float beta = (j * ei_hf + k * gf_di + l * dh_eg) / M;
    if(beta < 0 || beta > (1 - gamma)) {
        return false;
    }

    rec.t = t;
    rec.p = r.pointAtParameter(t);
    rec.normal = unitVector(cross(p2 - p1, p3 - p1));

    return true;
}