#include "FourMomentum.h"
#include <iostream>
#include <cmath>
#include <algorithm>

FourMomentum::FourMomentum() : components(4, 0.0) {}

FourMomentum::FourMomentum(double E, double px, double py, double pz) : components{E, px, py, pz} {
    validate();
}

void FourMomentum::validate() const {
    double E = components[0];
    double p = sqrt(components[1] * components[1] + components[2] * components[2] + components[3] * components[3]);
    if (E < p) {
        throw std::invalid_argument("Energy-momentum inconsistency: E must be greater than or equal to the magnitude of p.");
    }
}

double FourMomentum::getComponent(int index) const {
    if (index < 0 || index >= static_cast<int>(components.size())) {
        throw std::out_of_range("Index out of range in FourMomentum::getComponent.");
    }
    return components[index];
}

double FourMomentum::invariantMass() const {
    double E = components[0];
    double px = components[1];
    double py = components[2];
    double pz = components[3];
    double massSquared = E * E - (px * px + py * py + pz * pz);
    return std::sqrt(std::max(0.0, massSquared));
}

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
