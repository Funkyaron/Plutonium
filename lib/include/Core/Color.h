

#ifndef PLUTONIUM_COLOR_H
#define PLUTONIUM_COLOR_H


#include <array>


class Color {
public:

    Color() {}
    Color(float e0, float e1, float e2) : numbers({e0, e1, e2}) {}

    float r() const;
    float g() const;
    float b() const;

    const Color& operator+() const;
    Color operator-() const;

    Color& operator+=(const Color& other);
    Color& operator-=(const Color& other);
    Color& operator*=(const Color& other);
    Color& operator/=(const Color& other);
    Color& operator*=(const float t);
    Color& operator/=(const float t);

    void removeNaN();

private:

    std::array<float, 3> numbers;

};

Color operator+(const Color& lhs, const Color& rhs);
Color operator-(const Color& lhs, const Color& rhs);
Color operator*(const Color& lhs, const Color& rhs);
Color operator/(const Color& lhs, const Color& rhs);

Color operator*(float t, const Color& v);
Color operator*(const Color& v, float t);
Color operator/(const Color& v, float t);



#endif