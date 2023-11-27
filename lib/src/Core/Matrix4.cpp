


#include <algorithm>


#include "Matrix3.h"
#include "Matrix4.h"
#include "Vector3.h"
#include "Vector4.h"


Matrix4::Matrix4() {
    m00 = m01 = m02 = m03 = m10 = m11 = m12 = m13 = m20 = m21 = m22 = m23 = m30 = m31 = m32 = m33 = 0.0;
}

Matrix4::Matrix4(const Matrix3& rotAndScale, const Vector3& translation) {
    m00 = rotAndScale.get00();
    m01 = rotAndScale.get01();
    m02 = rotAndScale.get02();
    m03 = translation.x();
    m10 = rotAndScale.get10();
    m11 = rotAndScale.get11();
    m12 = rotAndScale.get12();
    m13 = translation.y();
    m20 = rotAndScale.get20();
    m21 = rotAndScale.get21();
    m22 = rotAndScale.get22();
    m23 = translation.z();
    m30 = 0.0;
    m31 = 0.0;
    m32 = 0.0;
    m33 = 1.0;
}

Matrix4 Matrix4::identity() {
    Matrix4 result;
    result.set00(1.0);
    result.set11(1.0);
    result.set22(1.0);
    result.set33(1.0);
    return result;
}

Matrix4 Matrix4::translation(float translateX, float translateY, float translateZ) {
    return Matrix4(Matrix3::identity(), Vector3(translateX, translateY, translateZ));
}

Matrix4 Matrix4::rotationX(float rotInDeg) {
    return Matrix4(Matrix3::rotationX(rotInDeg), Vector3(0.0, 0.0, 0.0));
}

Matrix4 Matrix4::rotationY(float rotInDeg) {
    return Matrix4(Matrix3::rotationY(rotInDeg), Vector3(0.0, 0.0, 0.0));
}

Matrix4 Matrix4::rotationZ(float rotInDeg) {
    return Matrix4(Matrix3::rotationZ(rotInDeg), Vector3(0.0, 0.0, 0.0));
}

Matrix4 Matrix4::scale(float scaleX, float scaleY, float scaleZ) {
    return Matrix4(Matrix3::scale(scaleX, scaleY, scaleZ), Vector3(0.0, 0.0, 0.0));
}

void Matrix4::transpose() {
    std::swap(m01, m10);
    std::swap(m02, m20);
    std::swap(m12, m21);
}

Matrix4 Matrix4::getTranspose() const {
    Matrix4 result = *this;
    result.set01(m10);
    result.set02(m20);
    result.set12(m21);
    result.set10(m01);
    result.set20(m02);
    result.set21(m12);
    return result;
}

void Matrix4::set00(float f) {
    m00 = f;
}

void Matrix4::set01(float f) {
    m01 = f;
}

void Matrix4::set02(float f) {
    m02 = f;
}

void Matrix4::set03(float f) {
    m03 = f;
}

void Matrix4::set10(float f) {
    m10 = f;
}

void Matrix4::set11(float f) {
    m11 = f;
}

void Matrix4::set12(float f) {
    m12 = f;
}

void Matrix4::set13(float f) {
    m13 = f;
}

void Matrix4::set20(float f) {
    m20 = f;
}

void Matrix4::set21(float f) {
    m21 = f;
}

void Matrix4::set22(float f) {
    m22 = f;
}

void Matrix4::set23(float f) {
    m23 = f;
}

void Matrix4::set30(float f) {
    m30 = f;
}

void Matrix4::set31(float f) {
    m31 = f;
}

void Matrix4::set32(float f) {
    m32 = f;
}

void Matrix4::set33(float f) {
    m33 = f;
}


Vector4 Matrix4::getRow0() const {
    return Vector4(m00, m01, m02, m03);
}

Vector4 Matrix4::getRow1() const {
    return Vector4(m10, m11, m12, m13);
}

Vector4 Matrix4::getRow2() const {
    return Vector4(m20, m21, m22, m23);
}

Vector4 Matrix4::getRow3() const {
    return Vector4(m30, m31, m32, m33);
}

Vector4 Matrix4::getColumn0() const {
    return Vector4(m00, m10, m20, m30);
}

Vector4 Matrix4::getColumn1() const {
    return Vector4(m01, m11, m21, m31);
}

Vector4 Matrix4::getColumn2() const {
    return Vector4(m02, m12, m22, m32);
}

Vector4 Matrix4::getColumn3() const {
    return Vector4(m03, m13, m23, m33);
}

Vector4 operator*(const Matrix4& m, const Vector4& v) {
    float x = dot(v, m.getRow0());
    float y = dot(v, m.getRow1());
    float z = dot(v, m.getRow2());
    float w = dot(v, m.getRow3());
    return Vector4(x, y, z, w);
}


Matrix4 operator*(const Matrix4& lhs, const Matrix4& rhs) {
    Matrix4 result;

    result.set00(dot(lhs.getRow0(), rhs.getColumn0()));
    result.set01(dot(lhs.getRow0(), rhs.getColumn1()));
    result.set02(dot(lhs.getRow0(), rhs.getColumn2()));
    result.set03(dot(lhs.getRow0(), rhs.getColumn3()));

    result.set10(dot(lhs.getRow1(), rhs.getColumn0()));
    result.set11(dot(lhs.getRow1(), rhs.getColumn1()));
    result.set12(dot(lhs.getRow1(), rhs.getColumn2()));
    result.set13(dot(lhs.getRow1(), rhs.getColumn3()));

    result.set20(dot(lhs.getRow2(), rhs.getColumn0()));
    result.set21(dot(lhs.getRow2(), rhs.getColumn1()));
    result.set22(dot(lhs.getRow2(), rhs.getColumn2()));
    result.set23(dot(lhs.getRow2(), rhs.getColumn3()));

    result.set30(dot(lhs.getRow3(), rhs.getColumn0()));
    result.set31(dot(lhs.getRow3(), rhs.getColumn1()));
    result.set32(dot(lhs.getRow3(), rhs.getColumn2()));
    result.set33(dot(lhs.getRow3(), rhs.getColumn3()));

    return result;
}