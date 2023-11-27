



#include "Matrix3.h"
#include "Vector3.h"

#include <numbers>
#include <math.h>
#include <algorithm>


Matrix3::Matrix3() {
    m00 = m01 = m02 = m10 = m11 = m12 = m20 = m21 = m22 = 0.0;
}


void Matrix3::set00(float f) {
    m00 = f;
}

void Matrix3::set01(float f) {
    m01 = f;
}

void Matrix3::set02(float f) {
    m02 = f;
}

void Matrix3::set10(float f) {
    m10 = f;
}

void Matrix3::set11(float f) {
    m11 = f;
}

void Matrix3::set12(float f) {
    m12 = f;
}

void Matrix3::set20(float f) {
    m20 = f;
}

void Matrix3::set21(float f) {
    m21 = f;
}

void Matrix3::set22(float f) {
    m22 = f;
}

float Matrix3::get00() const {
    return m00;
}

float Matrix3::get01() const {
    return m01;
}

float Matrix3::get02() const {
    return m02;
}

float Matrix3::get10() const {
    return m10;
}

float Matrix3::get11() const {
    return m11;
}

float Matrix3::get12() const {
    return m12;
}

float Matrix3::get20() const {
    return m20;
}

float Matrix3::get21() const {
    return m21;
}

float Matrix3::get22() const {
    return m22;
}

Vector3 Matrix3::getRow0() const {
    return Vector3(m00, m01, m02);
}

Vector3 Matrix3::getRow1() const {
    return Vector3(m10, m11, m12);
}

Vector3 Matrix3::getRow2() const {
    return Vector3(m20, m21, m22);
}

Vector3 Matrix3::getColumn0() const {
    return Vector3(m00, m10, m20);
}

Vector3 Matrix3::getColumn1() const {
    return Vector3(m01, m11, m21);
}

Vector3 Matrix3::getColumn2() const {
    return Vector3(m02, m12, m22);
}




Matrix3 Matrix3::identity() {
    Matrix3 result;
    result.set00(1.0);
    result.set11(1.0);
    result.set22(1.0);
    return result;
}

Matrix3 Matrix3::rotationX(float rotInDeg) {
    float rotInRad = rotInDeg * std::numbers::pi / 180.0;
    float cosinus = cos(rotInRad);
    float sinus = sin(rotInRad);

    Matrix3 result;
    result.set00(1.0);
    result.set11(cosinus);
    result.set12(-sinus);
    result.set21(sinus);
    result.set22(cosinus);
    return result;
}

Matrix3 Matrix3::rotationY(float rotInDeg) {
    float rotInRad = rotInDeg * std::numbers::pi / 180.0;
    float cosinus = cos(rotInRad);
    float sinus = sin(rotInRad);

    Matrix3 result;
    result.set11(1.0);
    result.set00(cosinus);
    result.set02(sinus);
    result.set20(-sinus);
    result.set22(cosinus);
    return result;
}

Matrix3 Matrix3::rotationZ(float rotInDeg) {
    float rotInRad = rotInDeg * std::numbers::pi / 180.0;
    float cosinus = cos(rotInRad);
    float sinus = sin(rotInRad);

    Matrix3 result;
    result.set22(1.0);
    result.set00(cosinus);
    result.set01(-sinus);
    result.set10(sinus);
    result.set11(cosinus);
    return result;
}

Matrix3 Matrix3::scale(float scaleX, float scaleY, float scaleZ) {
    Matrix3 result;
    result.set00(scaleX);
    result.set11(scaleY);
    result.set22(scaleZ);
    return result;
}

void Matrix3::transpose() {
    std::swap(m10, m01);
    std::swap(m20, m02);
    std::swap(m21, m12);
}

Matrix3 Matrix3::getTranspose() const {
    Matrix3 result = *this;
    result.set01(m10);
    result.set02(m20);
    result.set12(m21);
    result.set10(m01);
    result.set20(m02);
    result.set21(m12);
    return result;
}

Matrix3 operator+(const Matrix3& lhs, const Matrix3& rhs) {
    Matrix3 result;
    result.set00(lhs.get00() + rhs.get00());
    result.set01(lhs.get01() + rhs.get01());
    result.set02(lhs.get02() + rhs.get02());
    result.set10(lhs.get10() + rhs.get10());
    result.set11(lhs.get11() + rhs.get11());
    result.set12(lhs.get12() + rhs.get12());
    result.set20(lhs.get20() + rhs.get20());
    result.set21(lhs.get21() + rhs.get21());
    result.set22(lhs.get22() + rhs.get22());
    return result;
}

Matrix3 operator-(const Matrix3& lhs, const Matrix3& rhs) {
    Matrix3 result;
    result.set00(lhs.get00() - rhs.get00());
    result.set01(lhs.get01() - rhs.get01());
    result.set02(lhs.get02() - rhs.get02());
    result.set10(lhs.get10() - rhs.get10());
    result.set11(lhs.get11() - rhs.get11());
    result.set12(lhs.get12() - rhs.get12());
    result.set20(lhs.get20() - rhs.get20());
    result.set21(lhs.get21() - rhs.get21());
    result.set22(lhs.get22() - rhs.get22());
    return result;
}

Matrix3 operator*(float t, const Matrix3& m) {
    Matrix3 result;
    result.set00(m.get00() * t);
    result.set01(m.get01() * t);
    result.set02(m.get02() * t);
    result.set10(m.get10() * t);
    result.set11(m.get11() * t);
    result.set12(m.get12() * t);
    result.set20(m.get20() * t);
    result.set21(m.get21() * t);
    result.set22(m.get22() * t);
    return result;
}

Matrix3 operator*(const Matrix3& m, float t) {
    return t * m;
}

Matrix3 operator/(const Matrix3& m, float t) {
    float k = 1.0 / t;
    return k * m;
}

Vector3 operator*(const Matrix3& m, const Vector3& v) {
    float x = dot(v, m.getRow0());
    float y = dot(v, m.getRow1());
    float z = dot(v, m.getRow2());
    return Vector3(x, y, z);
}

Matrix3 operator*(const Matrix3& lhs, const Matrix3& rhs) {
    Matrix3 result;

    result.set00(dot(lhs.getRow0(), rhs.getColumn0()));
    result.set01(dot(lhs.getRow0(), rhs.getColumn1()));
    result.set02(dot(lhs.getRow0(), rhs.getColumn2()));

    result.set10(dot(lhs.getRow1(), rhs.getColumn0()));
    result.set11(dot(lhs.getRow1(), rhs.getColumn1()));
    result.set12(dot(lhs.getRow1(), rhs.getColumn2()));

    result.set20(dot(lhs.getRow2(), rhs.getColumn0()));
    result.set21(dot(lhs.getRow2(), rhs.getColumn1()));
    result.set22(dot(lhs.getRow2(), rhs.getColumn2()));

    return result;
}