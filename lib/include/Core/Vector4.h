



#ifndef PLUTONIUM_VECTOR4_h
#define PLUTONIUM_VECTOR4_h


#include <array>

class Vector3;


class Vector4 {
public:

    Vector4() {}
    Vector4(float x, float y, float z, float w) : numbers({x, y, z, w}) {}

    static Vector4 position(Vector3 v3);
    static Vector4 direction(Vector3 v3);

    operator Vector3() const;

    float x() const;
    float y() const;
    float z() const;
    float w() const;

private:

    std::array<float, 4> numbers;

};


float dot(const Vector4& lhs, const Vector4& rhs);




#endif