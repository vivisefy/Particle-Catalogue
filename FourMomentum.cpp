#include "FourMomentum.h"

FourMomentum::FourMomentum() : components(4, 0.0) {}

FourMomentum::FourMomentum(double E, double px, double py, double pz)
    : components{E, px, py, pz} {
    validate();
}

void FourMomentum::validate() const {
    double E = components[0];
    double p = sqrt(components[1] * components[1] + components[2] * components[2] + components[3] * components[3]);
    if (E < p) {
        throw std::invalid_argument("Energy-momentum inconsistency detected: E must be greater than or equal to |p|.");
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
    double mass2 = E * E - (px * px + py * py + pz * pz);
    return sqrt(std::max(0.0, mass2));
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
    for (int i = 0; i < 4; i++) {
        if (components[i] != other.components[i]) return true;
    }
    return false;
}
