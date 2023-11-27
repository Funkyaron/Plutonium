


#ifndef PLUTONIUM_MATRIX3_H
#define PLUTONIUM_MATRIX3_H


class Vector3;


class Matrix3 {
public:

    Matrix3();

    static Matrix3 identity();

    static Matrix3 rotationX(float rotInDeg);
    static Matrix3 rotationY(float rotInDeg);
    static Matrix3 rotationZ(float rotInDeg);

    static Matrix3 scale(float scaleX, float scaleY, float scaleZ);

    void transpose();
    Matrix3 getTranspose() const;

    void set00(float f);
    void set01(float f);
    void set02(float f);
    void set10(float f);
    void set11(float f);
    void set12(float f);
    void set20(float f);
    void set21(float f);
    void set22(float f);

    float get00() const;
    float get01() const;
    float get02() const;
    float get10() const;
    float get11() const;
    float get12() const;
    float get20() const;
    float get21() const;
    float get22() const;

    Vector3 getRow0() const;
    Vector3 getRow1() const;
    Vector3 getRow2() const;

    Vector3 getColumn0() const;
    Vector3 getColumn1() const;
    Vector3 getColumn2() const;

private:

    float m00, m01, m02, m10, m11, m12, m20, m21, m22;

};


Matrix3 operator+(const Matrix3& lhs, const Matrix3& rhs);
Matrix3 operator-(const Matrix3& lhs, const Matrix3& rhs);

Matrix3 operator*(float t, const Matrix3& m);
Matrix3 operator*(const Matrix3& m, float t);
Matrix3 operator/(const Matrix3& m, float t);

Vector3 operator*(const Matrix3& m, const Vector3& v);
Matrix3 operator*(const Matrix3& lhs, const Matrix3& rhs);






#endif