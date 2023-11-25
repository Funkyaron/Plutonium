



#include "Utility.h"
#include "Vector3.h"

#include <random>



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
}