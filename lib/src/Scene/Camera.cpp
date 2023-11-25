



#include "Camera.h"
#include "Ray.h"
#include "Utility.h"



Camera::Camera() {
    pixelWidth = 200;
    pixelHeight = 100;

    lowerLeftCorner = Vector3(-2.0, -1.0, -1.0);
    horizontal = Vector3(4.0, 0.0, 0.0);
    vertical = Vector3(0.0, 2.0, 0.0);
    origin = Vector3(0.0, 0.0, 0.0);
}

int Camera::getPixelWidth() const {
    return pixelWidth;
}

int Camera::getPixelHeight() const {
    return pixelHeight;
}

Ray Camera::getRayForPixel(int x, int y) const {
    float u = (float(x) + Plutonium::getRandomNumber()) / float(pixelWidth);
    float v = (float(pixelHeight - y - 1) + Plutonium::getRandomNumber()) / float(pixelHeight);

    Vector3 direction = lowerLeftCorner + u * horizontal + v * vertical;

    return Ray(origin, direction);
}