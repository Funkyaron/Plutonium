



#include "Utility.h"

#include <random>



namespace Plutonium {
    float getRandomNumber() {
        static std::default_random_engine generator;
        static std::uniform_real_distribution<float> distribution(0.0,1.0);
        return distribution(generator);
    }
}