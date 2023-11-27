




#include "Vector4.h"
#include "Vector3.h"



Vector4 Vector4::position(Vector3 v3) {
    return Vector4(v3.x(), v3.y(), v3.z(), 1.0);
}

Vector4 Vector4::direction(Vector3 v3) {
    return Vector4(v3.x(), v3.y(), v3.z(), 0.0);
}

Vector4::operator Vector3() const {
    return Vector3(numbers[0], numbers[1], numbers[2]);
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

float dot(const Vector4& lhs, const Vector4& rhs) {
    return lhs.x()*rhs.x() + lhs.y()*rhs.y() + lhs.z()*rhs.z() + lhs.w()*rhs.w();
}