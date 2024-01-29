



#ifndef PLUTONIUM_VECTOR4_h
#define PLUTONIUM_VECTOR4_h


#include <array>

class Vector3;


class Vector4 {
public:

    Vector4() {}
    Vector4(float x, float y, float z, float w) : numbers({x, y, z, w}) {}

    static Vector4 position(const Vector3& v3);
    static Vector4 direction(const Vector3& v3);

    float x() const;
    float y() const;
    float z() const;
    float w() const;

    const Vector4& operator+() const;
    Vector4 operator-() const;

    Vector4& operator+=(const Vector4& other);
    Vector4& operator-=(const Vector4& other);
    
    Vector4& operator*=(const float t);
    Vector4& operator/=(const float t);

    operator Vector3();

private:

    std::array<float, 4> numbers;

};


Vector4 operator+(const Vector4& lhs, const Vector4& rhs);
Vector4 operator-(const Vector4& lhs, const Vector4& rhs);

Vector4 operator*(float t, const Vector4& v);
Vector4 operator*(const Vector4& v, float t);
Vector4 operator/(const Vector4& v, float t);


float dot(const Vector4& lhs, const Vector4& rhs);




#endif