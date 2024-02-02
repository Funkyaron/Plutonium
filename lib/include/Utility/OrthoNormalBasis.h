

#ifndef PLUTONIUM_ORTHONORMALBASIS_H
#define PLUTONIUM_ORTHONORMALBASIS_H



#include "Vector3.h"

#include <array>



class OrthoNormalBasis {
public:

    OrthoNormalBasis() {}

    Vector3 operator[](int i) const;
    Vector3 u() const;
    Vector3 v() const;
    Vector3 w() const;
    Vector3 local(float a, float b, float c) const;
    Vector3 local(const Vector3& a) const;
    void buildFromW(const Vector3& n);

private:

    std::array<Vector3, 3> axes;

};







#endif