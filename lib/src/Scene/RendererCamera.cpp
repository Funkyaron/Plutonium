


#include <numbers>


#include "RendererCamera.h"
#include "Ray.h"
#include "Utility.h"



RendererCamera::RendererCamera() {
    pixelWidth = 200;
    pixelHeight = 100;

    origin = Vector3(0.0, 0.0, 0.0);
    lookAt = Vector3(0.0, 0.0, -1.0);
    verticalUp = Vector3(0.0, 1.0, 0.0);
    verticalFOV = 90.0;

    aperture = 0.0;
    focusDist = 1.0;

    pixelPlaneCalculated = false;
}

void RendererCamera::setResolution(int pixelWidth_, int pixelHeight_) {
    pixelWidth = pixelWidth_;
    pixelHeight = pixelHeight_;
    pixelPlaneCalculated = false;
}

void RendererCamera::setLookFrom(Vector3 lookFrom_) {
    origin = lookFrom_;
    pixelPlaneCalculated = false;
}

void RendererCamera::setLookAt(Vector3 lookAt_) {
    lookAt = lookAt_;
    pixelPlaneCalculated = false;
}

void RendererCamera::setVerticalUp(Vector3 verticalUp_) {
    verticalUp = verticalUp_;
    pixelPlaneCalculated = false;
}

void RendererCamera::setVerticalFOV(float verticalFOV_) {
    verticalFOV = verticalFOV_;
    pixelPlaneCalculated = false;
}

void RendererCamera::setAperture(float aperture_) {
    aperture = aperture_;
    pixelPlaneCalculated = false;
}

void RendererCamera::setFocusDist(float focusDist_) {
    focusDist = focusDist_;
    pixelPlaneCalculated = false;
}

int RendererCamera::getPixelWidth() const {
    return pixelWidth;
}

int RendererCamera::getPixelHeight() const {
    return pixelHeight;
}

Ray RendererCamera::getRayForPixel(int x, int y) {

    if(pixelPlaneCalculated == false) {
        calculatePixelPlane();
        pixelPlaneCalculated = true;
    }

    float s = (float(x) + Plutonium::getRandomNumber()) / float(pixelWidth);
    float t = (float(pixelHeight - y - 1) + Plutonium::getRandomNumber()) / float(pixelHeight);

    Vector3 rd = lensRadius * Plutonium::randomInUnitDisk();
    Vector3 offset = u * rd.x() + v * rd.y();
    Vector3 direction = lowerLeftCorner + s * horizontal + t * vertical - origin - offset;

    return Ray(origin + offset, direction);
}


void RendererCamera::calculatePixelPlane() {

    lensRadius = aperture / 2.0;

    float theta = verticalFOV * std::numbers::pi / 180.0;
    float halfHeight = tan(theta / 2.0);
    float halfWidth = float(pixelWidth) / float(pixelHeight) * halfHeight;

    w = unitVector(origin - lookAt);
    u = unitVector(cross(verticalUp, w));
    v = cross(w, u);

    lowerLeftCorner = origin - halfWidth * focusDist * u - halfHeight * focusDist * v - focusDist * w;
    horizontal = 2 * halfWidth * focusDist * u;
    vertical = 2 * halfHeight * focusDist * v;

}