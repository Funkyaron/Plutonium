




#ifndef PLUTONIUM_CAMERA_H
#define PLUTONIUM_CAMERA_H


#include "Vector3.h"


class Ray;


class Camera {
public:

    Camera();

    int getPixelWidth() const;
    int getPixelHeight() const;

    Ray getRayForPixel(int x, int y) const;

private:

    int pixelWidth;
    int pixelHeight;

    Vector3 origin;
    Vector3 lowerLeftCorner;
    Vector3 horizontal;
    Vector3 vertical;

};




#endif