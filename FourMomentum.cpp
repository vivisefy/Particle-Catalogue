#include "FourMomentum.h"
#include <cmath>  // For sqrt function
#include <stdexcept>  // For std::invalid_argument

// Default constructor initializes all components to zero
FourMomentum::FourMomentum() : components(4, 0.0) {}

// Parameterized constructor initializes components and validates the four-momentum
FourMomentum::FourMomentum(double E, double px, double py, double pz)
    : components{E, px, py, pz} {
    validate();
}

// Validates the four-momentum to ensure it adheres to the physical laws of relativity
void FourMomentum::validate() const {
    double E = components[0];
    double p = sqrt(components[1] * components[1] + components[2] * components[2] + components[3] * components[3]);
    if (E < p) {  // Check if the energy is less than the magnitude of the momentum vector
        throw std::invalid_argument("Energy-momentum inconsistency detected: E must be greater than or equal to |p|.");
    }
}

// Returns the component at the specified index with bounds checking
double FourMomentum::getComponent(int index) const {
    if (index < 0 || index >= components.size()) {
        throw std::out_of_range("Index out of range in FourMomentum::getComponent.");
    }
    return components.at(index);
}

// Calculates the invariant mass using the energy and momentum components
double FourMomentum::invariantMass() const {
    double E = components[0];
    double px = components[1];
    double py = components[2];
    double pz = components[3];
    double mass2 = E * E - px * px - py * py - pz * pz; // m^2 = E^2 - |p|^2
    return sqrt(std::max(0.0, mass2));  // Ensure no negative square root is taken
}

// Adds two FourMomenta and returns the resulting FourMomentum
FourMomentum FourMomentum::operator+(const FourMomentum& other) const {
    return FourMomentum(
        components[0] + other.components[0],
        components[1] + other.components[1],
        components[2] + other.components[2],
        components[3] + other.components[3]);
}

// Subtracts one FourMomentum from another and returns the result
FourMomentum FourMomentum::operator-(const FourMomentum& other) const {
    return FourMomentum(
        components[0] - other.components[0],
        components[1] - other.components[1],
        components[2] - other.components[2],
        components[3] - other.components[3]);
}

// Calculates the dot product of two FourMomenta
double FourMomentum::operator*(const FourMomentum& other) const {
    return components[0] * other.components[0] -
           components[1] * other.components[1] -
           components[2] * other.components[2] -
           components[3] * other.components[3];
}

// Adds another FourMomentum to this object and updates it
FourMomentum& FourMomentum::operator+=(const FourMomentum& other) {
    for (int i = 0; i < 4; i++) {
        components[i] += other.components[i];
    }
    validate();  // Re-validate after modification
    return *this;
}

// Compares two FourMomenta for inequality
bool FourMomentum::operator!=(const FourMomentum& other) const {
    for (int i = 0; i < 4; i++) {
        if (components[i] != other.components[i]) return true;
    }
    return false;
}
