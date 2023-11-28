




#include "Vector4.h"
#include "Vector3.h"



Vector4 Vector4::position(Vector3 v3) {
    return Vector4(v3.x(), v3.y(), v3.z(), 1.0);
}

Vector4 Vector4::direction(Vector3 v3) {
    return Vector4(v3.x(), v3.y(), v3.z(), 0.0);
}

float Vector4::x() const {
    return numbers[0];
}

float Vector4::y() const {
    return numbers[1];
}

float Vector4::z() const {
    return numbers[2];
}

float Vector4::w() const {
    return numbers[3];
}


const Vector4& Vector4::operator+() const {
    return *this;
}

Vector4 Vector4::operator-() const {
    return Vector4(-numbers[0], -numbers[1], -numbers[2], -numbers[3]);
}

Vector4& Vector4::operator+=(const Vector4& other) {
    numbers[0] += other.x();
    numbers[1] += other.y();
    numbers[2] += other.z();
    numbers[3] += other.w();
    return *this;
}

Vector4& Vector4::operator-=(const Vector4& other) {
    numbers[0] -= other.x();
    numbers[1] -= other.y();
    numbers[2] -= other.z();
    numbers[3] -= other.w();
    return *this;
}

Vector4& Vector4::operator*=(const float t) {
    numbers[0] *= t;
    numbers[1] *= t;
    numbers[2] *= t;
    numbers[3] *= t;
    return *this;
}

Vector4& Vector4::operator/=(const float t) {
    float k = 1.0f / t;
    numbers[0] *= k;
    numbers[1] *= k;
    numbers[2] *= k;
    numbers[3] *= k;
    return *this;
}


Vector4 operator+(const Vector4& lhs, const Vector4& rhs) {
    return Vector4(lhs.x() + rhs.x(), lhs.y() + rhs.y(), lhs.z() + rhs.z(), lhs.w() + rhs.w());
}

Vector4 operator-(const Vector4& lhs, const Vector4& rhs) {
    return Vector4(lhs.x() - rhs.x(), lhs.y() - rhs.y(), lhs.z() - rhs.z(), lhs.w() - rhs.w());
}

Vector4 operator*(float t, const Vector4& v) {
    return Vector4(v.x() * t, v.y() * t, v.z() * t, v.w() * t);
}

Vector4 operator*(const Vector4& v, float t) {
    return Vector4(v.x() * t, v.y() * t, v.z() * t, v.w() * t);
}

Vector4 operator/(const Vector4& v, float t) {
    return Vector4(v.x() / t, v.y() / t, v.z() / t, v.w() / t);
}



float dot(const Vector4& lhs, const Vector4& rhs) {
    return lhs.x()*rhs.x() + lhs.y()*rhs.y() + lhs.z()*rhs.z() + lhs.w()*rhs.w();
}
