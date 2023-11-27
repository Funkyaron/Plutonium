



#ifndef PLUTONIUM_MATRIX4_h
#define PLUTONIUM_MATRIX4_h


class Matrix3;
class Vector3;
class Vector4;


class Matrix4 {
public:

    Matrix4();
    Matrix4(const Matrix3& rotAndScale, const Vector3& translation);

    static Matrix4 identity();

    static Matrix4 translation(float translateX, float translateY, float translateZ);

    static Matrix4 rotationX(float rotInDeg);
    static Matrix4 rotationY(float rotInDeg);
    static Matrix4 rotationZ(float rotInDeg);

    static Matrix4 scale(float scaleX, float scaleY, float scaleZ);

    void transpose();
    Matrix4 getTranspose() const;

    void set00(float f);
    void set01(float f);
    void set02(float f);
    void set03(float f);
    void set10(float f);
    void set11(float f);
    void set12(float f);
    void set13(float f);
    void set20(float f);
    void set21(float f);
    void set22(float f);
    void set23(float f);
    void set30(float f);
    void set31(float f);
    void set32(float f);
    void set33(float f);

    Vector4 getRow0() const;
    Vector4 getRow1() const;
    Vector4 getRow2() const;
    Vector4 getRow3() const;

    Vector4 getColumn0() const;
    Vector4 getColumn1() const;
    Vector4 getColumn2() const;
    Vector4 getColumn3() const;

private:

    float m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33;

};


Vector4 operator*(const Matrix4& m, const Vector4& v);
Matrix4 operator*(const Matrix4& lhs, const Matrix4& rhs);




#endif