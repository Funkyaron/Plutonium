



#include "ProbabilityDensityFunction.h"
#include "Utility.h"



float BoxListProbabilityDensityFunction::value(const Vector3& direction) const {
    if(boxes.empty()) {
        return 0.0;
    }
    float sum = 0.0;
    for(auto &box : boxes) {
        sum += BoxProbabilityDensityFunction(box, origin).value(direction);
    }
    return sum / float(boxes.size());
}

Vector3 BoxListProbabilityDensityFunction::generate() const {
    if(boxes.empty()) {
        // I don't want the algorithm to break when there are no lights or anything consiered "important" in the scene,
        // so just randomly return up vector
        return Vector3(0.0, 1.0, 0.0);
    }
    float boxDecide = Plutonium::getRandomNumber() * float(boxes.size());
    for(int i = 0; i < boxes.size(); i++) {
        if(boxDecide < float(i + 1)) {
            return BoxProbabilityDensityFunction(boxes[i], origin).generate();
        }
    }
    // We shouldn't be able to leave the for loop without getting to return anything, but just in case:
    return BoxProbabilityDensityFunction(boxes.back(), origin).generate();
}
