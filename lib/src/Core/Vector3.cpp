



#include "Vector3.h"
#include "Color.h"

#include <math.h>



float Vector3::x() const {
    return numbers[0];
}

float Vector3::y() const {
    return numbers[1];
}

float Vector3::z() const {
    return numbers[2];
}


const Vector3& Vector3::operator+() const {
    return *this;
}

Vector3 Vector3::operator-() const {
    return Vector3(-numbers[0], -numbers[1], -numbers[2]);
}

Vector3& Vector3::operator+=(const Vector3& other) {
    numbers[0] += other.x();
    numbers[1] += other.y();
    numbers[2] += other.z();
    return *this;
}

Vector3& Vector3::operator-=(const Vector3& other) {
    numbers[0] -= other.x();
    numbers[1] -= other.y();
    numbers[2] -= other.z();
    return *this;
}

Vector3& Vector3::operator*=(const float t) {
    numbers[0] *= t;
    numbers[1] *= t;
    numbers[2] *= t;
    return *this;
}

Vector3& Vector3::operator/=(const float t) {
    float k = 1.0f / t;
    numbers[0] *= k;
    numbers[1] *= k;
    numbers[2] *= k;
    return *this;
}

float Vector3::length() const {
    return sqrt(numbers[0]*numbers[0] + numbers[1]*numbers[1] + numbers[2]*numbers[2]);
}

float Vector3::squaredLength() const {
    return numbers[0]*numbers[0] + numbers[1]*numbers[1] + numbers[2]*numbers[2];
}

void Vector3::normalize() {
    float k = 1.0f / sqrt(numbers[0]*numbers[0] + numbers[1]*numbers[1] + numbers[2]*numbers[2]);
    numbers[0] *= k;
    numbers[1] *= k;
    numbers[2] *= k;
}

Color Vector3::convertToColor() {
    return Color(numbers[0], numbers[1], numbers[2]);
}


Vector3 operator+(const Vector3& lhs, const Vector3& rhs) {
    return Vector3(lhs.x() + rhs.x(), lhs.y() + rhs.y(), lhs.z() + rhs.z());
}

Vector3 operator-(const Vector3& lhs, const Vector3& rhs) {
    return Vector3(lhs.x() - rhs.x(), lhs.y() - rhs.y(), lhs.z() - rhs.z());
}

Vector3 operator*(float t, const Vector3& v) {
    return Vector3(v.x() * t, v.y() * t, v.z() * t);
}

Vector3 operator*(const Vector3& v, float t) {
    return Vector3(v.x() * t, v.y() * t, v.z() * t);
}

Vector3 operator/(const Vector3& v, float t) {
    return Vector3(v.x() / t, v.y() / t, v.z() / t);
}

float dot(const Vector3& lhs, const Vector3& rhs) {
    return lhs.x()*rhs.x() + lhs.y()*rhs.y() + lhs.z()*rhs.z();
}

Vector3 cross(const Vector3& lhs, const Vector3& rhs) {
    return Vector3((lhs.y() * rhs.z() - lhs.z() * rhs.y()),
                    (-(lhs.x() * rhs.z() - lhs.z() * rhs.x())),
                    (lhs.x() * rhs.y() - lhs.y() * rhs.x()));
}

Vector3 unitVector(Vector3 v) {
    return v / v.length();
}

Vector3 reflect(const Vector3& v, const Vector3& n) {
    return v - 2.0 * dot(v, n) * n;
}
