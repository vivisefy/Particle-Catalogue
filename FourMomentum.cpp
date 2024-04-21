#include "FourMomentum.h"

FourMomentum FourMomentum::operator+(const FourMomentum& other) const {
    return FourMomentum(components[0] + other.components[0],
                        components[1] + other.components[1],
                        components[2] + other.components[2],
                        components[3] + other.components[3]);
}

FourMomentum FourMomentum::operator-(const FourMomentum& other) const {
    return FourMomentum(components[0] - other.components[0],
                        components[1] - other.components[1],
                        components[2] - other.components[2],
                        components[3] - other.components[3]);
}

double FourMomentum::operator*(const FourMomentum& other) const {
    return components[0] * other.components[0] - 
           (components[1] * other.components[1] + 
            components[2] * other.components[2] + 
            components[3] * other.components[3]);
}

FourMomentum& FourMomentum::operator+=(const FourMomentum& other) {
    for (int i = 0; i < 4; i++) {
        components[i] += other.components[i];
    }
    validate();
    return *this;
}

bool FourMomentum::operator!=(const FourMomentum& other) const {
    return !std::equal(components.begin(), components.end(), other.components.begin());
}

void FourMomentum::adjustForPhysicalConsistency(double expectedMass) {
    double currentMass = invariantMass();
    if (std::abs(currentMass - expectedMass) > 1e-4) {
        double factor = expectedMass / currentMass;
        for (int i = 1; i < 4; i++) {
            components[i] *= factor;
        }
        components[0] = std::sqrt(components[1]*components[1] + components[2]*components[2] + components[3]*components[3] + expectedMass*expectedMass);
    }
}
