
#ifndef PLUTONIUM_VECTOR3_H
#define PLUTONIUM_VECTOR3_H



#include <array>



class Vector3 {
public:

    Vector3() {}
    Vector3(float e0, float e1, float e2) : numbers({e0, e1, e2}) {}

    float x() const;
    float y() const;
    float z() const;

    const Vector3& operator+() const;
    Vector3 operator-() const;

    Vector3& operator+=(const Vector3& other);
    Vector3& operator-=(const Vector3& other);
    
    Vector3& operator*=(const float t);
    Vector3& operator/=(const float t);

    float length() const;
    float squared_length() const;
    void normalize();

private:

    std::array<float, 3> numbers;

};


Vector3 operator+(const Vector3& lhs, const Vector3& rhs);
Vector3 operator-(const Vector3& lhs, const Vector3& rhs);

Vector3 operator*(float t, const Vector3& v);
Vector3 operator*(const Vector3& v, float t);
Vector3 operator/(const Vector3& v, float t);

float dot(const Vector3& lhs, const Vector3& rhs);
Vector3 cross(const Vector3& lhs, const Vector3& rhs);

Vector3 unitVector(Vector3 v);



#endif