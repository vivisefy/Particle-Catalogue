#ifndef FOURMOMENTUM_H
#define FOURMOMENTUM_H

#include <vector>
#include <cmath>
#include <stdexcept>

class FourMomentum {
private:
    std::vector<double> components;  // Stores the four-momentum components [E, px, py, pz]

public:
    FourMomentum();  // Default constructor initializes four-vector to zero
    explicit FourMomentum(double E, double px, double py, double pz);  // Parameterized constructor
    void validate() const;  // Validates the energy-momentum relation
    double getComponent(int index) const;  // Returns the specified component of the four-momentum
    double invariantMass() const;  // Calculates and returns the invariant mass
    FourMomentum operator+(const FourMomentum& other) const;  // Adds two four-momenta
    FourMomentum operator-(const FourMomentum& other) const;  // Subtracts two four-momenta
    double operator*(const FourMomentum& other) const;  // Calculates the dot product
    FourMomentum& operator+=(const FourMomentum& other);  // Adds another four-momentum to this one
    bool operator!=(const FourMomentum& other) const;  // Checks for inequality
    void adjustForPhysicalConsistency(double expectedMass);  // Adjusts the vector to ensure physical consistency
};

#endif // FOURMOMENTUM_H
