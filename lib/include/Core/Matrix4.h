



#ifndef PLUTONIUM_MATRIX4_h
#define PLUTONIUM_MATRIX4_h


class Vector3;
class Vector4;



class Matrix4 {
public:

    // Rule of 5
    Matrix4();
    ~Matrix4();
    Matrix4(const Matrix4& other);
    Matrix4(Matrix4&& other);
    Matrix4& operator=(const Matrix4& other);
    Matrix4& operator=(Matrix4&& other);

    void copyContent(float* dest) const;
    void moveContent(float** dest);

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

    float get00() const;
    float get01() const;
    float get02() const;
    float get03() const;
    float get10() const;
    float get11() const;
    float get12() const;
    float get13() const;
    float get20() const;
    float get21() const;
    float get22() const;
    float get23() const;
    float get30() const;
    float get31() const;
    float get32() const;
    float get33() const;


private:

    float* content;

};


Vector4 operator*(const Matrix4& m, const Vector4& v);
Matrix4 operator*(const Matrix4& lhs, const Matrix4& rhs);




#endif