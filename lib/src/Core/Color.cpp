



#include "Color.h"




float Color::r() const {
    return numbers[0];
}

float Color::g() const {
    return numbers[1];
}

float Color::b() const {
    return numbers[2];
}

const Color& Color::operator+() const {
    return *this;
}

Color Color::operator-() const {
    return Color(-numbers[0], -numbers[1], -numbers[2]);
}

Color& Color::operator+=(const Color& other) {
    numbers[0] += other.r();
    numbers[1] += other.g();
    numbers[2] += other.b();
    return *this;
}

Color& Color::operator-=(const Color& other) {
    numbers[0] -= other.r();
    numbers[1] -= other.g();
    numbers[2] -= other.b();
    return *this;
}

Color& Color::operator*=(const Color& other) {
    numbers[0] *= other.r();
    numbers[1] *= other.g();
    numbers[2] *= other.b();
    return *this;
}

Color& Color::operator/=(const Color& other) {
    numbers[0] /= other.r();
    numbers[1] /= other.g();
    numbers[2] /= other.b();
    return *this;
}

Color& Color::operator*=(const float t) {
    numbers[0] *= t;
    numbers[1] *= t;
    numbers[2] *= t;
    return *this;
}

Color& Color::operator/=(const float t) {
    float k = 1.0f / t;
    numbers[0] *= k;
    numbers[1] *= k;
    numbers[2] *= k;
    return *this;
}

Color operator+(const Color& lhs, const Color& rhs) {
    return Color(lhs.r() + rhs.r(), lhs.g() + rhs.g(), lhs.b() + rhs.b());
}

Color operator-(const Color& lhs, const Color& rhs) {
    return Color(lhs.r() - rhs.r(), lhs.g() - rhs.g(), lhs.b() - rhs.b());
}

Color operator*(const Color& lhs, const Color& rhs) {
    return Color(lhs.r() * rhs.r(), lhs.g() * rhs.g(), lhs.b() * rhs.b());
}

Color operator/(const Color& lhs, const Color& rhs) {
    return Color(lhs.r() / rhs.r(), lhs.g() / rhs.g(), lhs.b() / rhs.b());
}

Color operator*(float t, const Color& c) {
    return Color(c.r() * t, c.g() * t, c.b() * t);
}

Color operator*(const Color& c, float t) {
    return Color(c.r() * t, c.g() * t, c.b() * t);
}

Color operator/(const Color& c, float t) {
    return Color(c.r() / t, c.g() / t, c.b() / t);
}


void Color::removeNaN() {
    for(int i = 0; i < 3; i++) {
        if(!(numbers[i] == numbers[i])) {
            numbers[i] = 0.0;
        }
    }
}
