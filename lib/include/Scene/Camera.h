




#ifndef PLUTONIUM_CAMERA_H
#define PLUTONIUM_CAMERA_H


#include "Vector3.h"


class Ray;


class Camera {
public:

    Camera();

    void setResolution(int pixelWidth_, int pixelHeight_);
    void setLookFrom(Vector3 lookFrom_);
    void setLookAt(Vector3 lookAt_);
    void setVerticalUp(Vector3 verticalUp_);
    void setVerticalFOV(float verticalFOV_);
    void setAperture(float aperture_);
    void setFocusDist(float focusDist_);

    int getPixelWidth() const;
    int getPixelHeight() const;

    Ray getRayForPixel(int x, int y);

private:

    void calculatePixelPlane();

    int pixelWidth;
    int pixelHeight;

    Vector3 lookAt;
    Vector3 verticalUp;
    float verticalFOV;

    float aperture;
    float focusDist;

    Vector3 origin;
    Vector3 lowerLeftCorner;
    Vector3 horizontal;
    Vector3 vertical;
    Vector3 u, v, w;
    float lensRadius;

    bool pixelPlaneCalculated;

};




#endif