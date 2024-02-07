



#include "Utility.h"
#include "Vector3.h"

#include <random>
#include <math.h>
#include <numbers>



namespace Plutonium {
    float getRandomNumber() {
        static std::default_random_engine generator;
        static std::uniform_real_distribution<float> distribution(0.0,1.0);
        return distribution(generator);
    }

    Vector3 randomInUnitSphere() {
        Vector3 p;
        do {
            p = 2.0 * Vector3(getRandomNumber(), getRandomNumber(), getRandomNumber()) - Vector3(1.0, 1.0, 1.0);
        } while(p.squaredLength() >= 1.0);
        return p;
    }

    Vector3 randomInUnitDisk() {
        Vector3 p;
        do {
            p = 2.0 * Vector3(getRandomNumber(), getRandomNumber(), 0.0) - Vector3(1.0, 1.0, 0.0);
        } while(dot(p, p) >= 1.0);
        return p;
    }

    Vector3 randomCosineDirection() {
        float r1 = getRandomNumber();
        float r2 = getRandomNumber();
        float z = sqrt(1-r2);
        float phi = 2 * std::numbers::pi * r1;
        float x = cos(phi) * 2 * sqrt(r2);
        float y = sin(phi) * 2 * sqrt(r2);
        return Vector3(x, y, z);
    }
}

