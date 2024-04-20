#include "FourMomentum.h"

FourMomentum::FourMomentum(double E, double px, double py, double pz) : components{E, px, py, pz} {
    validate();
}

void FourMomentum::validate() const {
    double E = components[0];
    double p = sqrt(components[1]*components[1] + components[2]*components[2] + components[3]*components[3]);
    if (E < p) {
        throw std::invalid_argument("Energy-momentum inconsistency detected.");
    }
}

double FourMomentum::getComponent(int index) const {
    return components.at(index);
}

double FourMomentum::invariantMass() const {
    double E = components[0];
    double px = components[1];
    double py = components[2];
    double pz = components[3];
    return sqrt(E*E - px*px - py*py - pz*pz);
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
           components[1] * other.components[1] -
           components[2] * other.components[2] -
           components[3] * other.components[3];
}
