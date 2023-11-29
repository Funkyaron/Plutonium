


#include <algorithm>
#include <cstring>
#include <math.h>


#include "Matrix3.h"
#include "Matrix4.h"
#include "Vector3.h"
#include "Vector4.h"


Matrix4::Matrix4() {
    content = new float[16];
    for(int i = 0; i < 16; i++) {
        content[i] = 0.0;
    }
}

Matrix4::~Matrix4() {
    delete content;
}

Matrix4::Matrix4(const Matrix4& other) {
    content = new float[16];
    std::memcpy(content, other.getContentRawPtr(), 16 * sizeof(float));
}

Matrix4::Matrix4(Matrix4&& other) {
    content = other.getContentRawPtr();
    other.setContentRawPtr(nullptr);
}

Matrix4& Matrix4::operator=(const Matrix4& other) {
    return *this = Matrix4(other);
}

Matrix4& Matrix4::operator=(Matrix4&& other) {
    content = other.getContentRawPtr();
    other.setContentRawPtr(nullptr);
    return *this;
}


float* Matrix4::getContentRawPtr() const {
    return content;
}

void Matrix4::setContentRawPtr(float* newPtr) {
    content = newPtr;
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
    Matrix4 result;
    result.set00(1.0);
    result.set11(1.0);
    result.set22(1.0);
    result.set33(1.0);
    result.set03(translateX);
    result.set13(translateY);
    result.set23(translateZ);
    return result;
}

Matrix4 Matrix4::rotationX(float rotInDeg) {
    float rotInRad = rotInDeg * std::numbers::pi / 180.0;
    float cosinus = cos(rotInRad);
    float sinus = sin(rotInRad);

    Matrix4 result;
    result.set00(1.0);
    result.set11(cosinus);
    result.set12(-sinus);
    result.set21(sinus);
    result.set22(cosinus);
    result.set33(1.0);
    return result;
}

Matrix4 Matrix4::rotationY(float rotInDeg) {
    float rotInRad = rotInDeg * std::numbers::pi / 180.0;
    float cosinus = cos(rotInRad);
    float sinus = sin(rotInRad);

    Matrix4 result;
    result.set11(1.0);
    result.set00(cosinus);
    result.set02(sinus);
    result.set20(-sinus);
    result.set22(cosinus);
    result.set33(1.0);
    return result;
}

Matrix4 Matrix4::rotationZ(float rotInDeg) {
    float rotInRad = rotInDeg * std::numbers::pi / 180.0;
    float cosinus = cos(rotInRad);
    float sinus = sin(rotInRad);

    Matrix4 result;
    result.set22(1.0);
    result.set00(cosinus);
    result.set01(-sinus);
    result.set10(sinus);
    result.set11(cosinus);
    result.set33(1.0);
    return result;
}

Matrix4 Matrix4::scale(float scaleX, float scaleY, float scaleZ) {
    Matrix4 result;
    result.set00(scaleX);
    result.set11(scaleY);
    result.set22(scaleZ);
    result.set33(1.0);
    return result;
}

void Matrix4::transpose() {
    std::swap(content[1], content[4]);
    std::swap(content[2], content[8]);
    std::swap(content[6], content[9]);
}

Matrix4 Matrix4::getTranspose() const {
    Matrix4 result = *this;
    result.set01(content[4]);
    result.set02(content[8]);
    result.set12(content[9]);
    result.set10(content[1]);
    result.set20(content[2]);
    result.set21(content[6]);
    return result;
}

void Matrix4::set00(float f) {
    content[0] = f;
}

void Matrix4::set01(float f) {
    content[1] = f;
}

void Matrix4::set02(float f) {
    content[2] = f;
}

void Matrix4::set03(float f) {
    content[3] = f;
}

void Matrix4::set10(float f) {
    content[4] = f;
}

void Matrix4::set11(float f) {
    content[5] = f;
}

void Matrix4::set12(float f) {
    content[6] = f;
}

void Matrix4::set13(float f) {
    content[7] = f;
}

void Matrix4::set20(float f) {
    content[8] = f;
}

void Matrix4::set21(float f) {
    content[9] = f;
}

void Matrix4::set22(float f) {
    content[10] = f;
}

void Matrix4::set23(float f) {
    content[11] = f;
}

void Matrix4::set30(float f) {
    content[12] = f;
}

void Matrix4::set31(float f) {
    content[13] = f;
}

void Matrix4::set32(float f) {
    content[14] = f;
}

void Matrix4::set33(float f) {
    content[15] = f;
}


float Matrix4::get00() const {
    return content[0];
}

float Matrix4::get01() const {
    return content[1];
}

float Matrix4::get02() const {
    return content[2];
}

float Matrix4::get03() const {
    return content[3];
}

float Matrix4::get10() const {
    return content[4];
}

float Matrix4::get11() const {
    return content[5];
}

float Matrix4::get12() const {
    return content[6];
}

float Matrix4::get13() const {
    return content[7];
}

float Matrix4::get20() const {
    return content[8];
}

float Matrix4::get21() const {
    return content[9];
}

float Matrix4::get22() const {
    return content[10];
}

float Matrix4::get23() const {
    return content[11];
}

float Matrix4::get30() const {
    return content[12];
}

float Matrix4::get31() const {
    return content[13];
}

float Matrix4::get32() const {
    return content[14];
}

float Matrix4::get33() const {
    return content[15];
}




Vector4 operator*(const Matrix4& m, const Vector4& v) {
    float x = m.get00() * v.x() + m.get01() * v.y() + m.get02() * v.z() + m.get03() * v.w();
    float y = m.get10() * v.x() + m.get11() * v.y() + m.get12() * v.z() + m.get13() * v.w();
    float z = m.get20() * v.x() + m.get21() * v.y() + m.get22() * v.z() + m.get23() * v.w();
    float w = m.get30() * v.x() + m.get31() * v.y() + m.get32() * v.z() + m.get33() * v.w();
    return Vector4(x, y, z, w);
}


Matrix4 operator*(const Matrix4& lhs, const Matrix4& rhs) {
    Matrix4 result;

    result.set00(lhs.get00() * rhs.get00() + lhs.get01() * rhs.get10() + lhs.get02() * rhs.get20() + lhs.get03() * rhs.get30());
    result.set01(lhs.get00() * rhs.get01() + lhs.get01() * rhs.get11() + lhs.get02() * rhs.get21() + lhs.get03() * rhs.get31());
    result.set02(lhs.get00() * rhs.get02() + lhs.get01() * rhs.get12() + lhs.get02() * rhs.get22() + lhs.get03() * rhs.get32());
    result.set03(lhs.get00() * rhs.get03() + lhs.get01() * rhs.get13() + lhs.get02() * rhs.get23() + lhs.get03() * rhs.get33());

    result.set10(lhs.get10() * rhs.get00() + lhs.get11() * rhs.get10() + lhs.get12() * rhs.get20() + lhs.get13() * rhs.get30());
    result.set11(lhs.get10() * rhs.get01() + lhs.get11() * rhs.get11() + lhs.get12() * rhs.get21() + lhs.get13() * rhs.get31());
    result.set12(lhs.get10() * rhs.get02() + lhs.get11() * rhs.get12() + lhs.get12() * rhs.get22() + lhs.get13() * rhs.get32());
    result.set13(lhs.get10() * rhs.get03() + lhs.get11() * rhs.get13() + lhs.get12() * rhs.get23() + lhs.get13() * rhs.get33());

    result.set20(lhs.get20() * rhs.get00() + lhs.get21() * rhs.get10() + lhs.get22() * rhs.get20() + lhs.get23() * rhs.get30());
    result.set21(lhs.get20() * rhs.get01() + lhs.get21() * rhs.get11() + lhs.get22() * rhs.get21() + lhs.get23() * rhs.get31());
    result.set22(lhs.get20() * rhs.get02() + lhs.get21() * rhs.get12() + lhs.get22() * rhs.get22() + lhs.get23() * rhs.get32());
    result.set23(lhs.get20() * rhs.get03() + lhs.get21() * rhs.get13() + lhs.get22() * rhs.get23() + lhs.get23() * rhs.get33());

    result.set30(lhs.get30() * rhs.get00() + lhs.get31() * rhs.get10() + lhs.get32() * rhs.get20() + lhs.get33() * rhs.get30());
    result.set31(lhs.get30() * rhs.get01() + lhs.get31() * rhs.get11() + lhs.get32() * rhs.get21() + lhs.get33() * rhs.get31());
    result.set32(lhs.get30() * rhs.get02() + lhs.get31() * rhs.get12() + lhs.get32() * rhs.get22() + lhs.get33() * rhs.get32());
    result.set33(lhs.get30() * rhs.get03() + lhs.get31() * rhs.get13() + lhs.get32() * rhs.get23() + lhs.get33() * rhs.get33());

    return result;
}

