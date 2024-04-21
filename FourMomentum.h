#ifndef FOURMOMENTUM_H
#define FOURMOMENTUM_H

#include <vector>
#include <cmath>
#include <stdexcept>
#include <iostream> // Added for logging

class FourMomentum {
private:
    std::vector<double> components;  // Stores the four-momentum components [E, px, py, pz]

public:
    FourMomentum() : components(4, 0.0) {}  // Default constructor initializes four-vector to zero
    FourMomentum(double E, double px, double py, double pz) : components{E, px, py, pz} {
        validate();
    }

    // Validate energy-momentum relation
    void validate() const {
        double E = components[0];
        double p = sqrt(components[1] * components[1] + components[2] * components[2] + components[3] * components[3]);
        if (E < p) {
            std::cerr << "Validation Error: Energy (" << E << ") is less than the magnitude of momentum (" << p << ")." << std::endl;
            throw std::invalid_argument("Energy-momentum inconsistency: E must be greater than or equal to the magnitude of p.");
        }
    }

    double getComponent(int index) const {
        if (index < 0 || index >= static_cast<int>(components.size())) {
            throw std::out_of_range("Index out of range in FourMomentum::getComponent.");
        }
        return components[index];
    }

    double invariantMass() const {
        double E = components[0];
        double px = components[1];
        double py = components[2];
        double pz = components[3];
        double massSquared = E * E - (px * px + py * py + pz * pz);
        return std::sqrt(std::max(0.0, massSquared));
    }

    FourMomentum operator+(const FourMomentum& other) const;
    FourMomentum operator-(const FourMomentum& other) const;
    double operator*(const FourMomentum& other) const;
    FourMomentum& operator+=(const FourMomentum& other);
    bool operator!=(const FourMomentum& other) const;
    void adjustForPhysicalConsistency(double expectedMass); // Adjusts the components to ensure physical consistency based on expected mass
};

#endif // FOURMOMENTUM_H
