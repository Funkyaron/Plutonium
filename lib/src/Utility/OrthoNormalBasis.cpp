


#include "OrthoNormalBasis.h"

#include <math.h>



Vector3 OrthoNormalBasis::operator[](int i) const {
    return axes[i];
}

Vector3 OrthoNormalBasis::u() const {
    return axes[0];
}

Vector3 OrthoNormalBasis::v() const {
    return axes[1];
}

Vector3 OrthoNormalBasis::w() const {
    return axes[2];
}

Vector3 OrthoNormalBasis::local(float a, float b, float c) const {
    return a * u() + b * v() + c * w();
}

Vector3 OrthoNormalBasis::local(const Vector3& a) const {
    return a.x() * u() + a.y() * v() + a.z() * w();
}

void OrthoNormalBasis::buildFromW(const Vector3& n) {
    axes[2] = unitVector(n);
    Vector3 a;
    if(fabs(w().x()) > 0.9) {
        a = Vector3(0.0, 1.0, 0.0);
    }
    else {
        a = Vector3(1.0, 0.0, 0.0);
    }
    axes[1] = unitVector(cross(w(), a));
    axes[0] = cross(w(), v());
}