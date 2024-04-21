#ifndef FOURMOMENTUM_H
#define FOURMOMENTUM_H

#include <vector>
#include <cmath>
#include <stdexcept>

class FourMomentum {
private:
    std::vector<double> components;  // Stores the four-momentum components (E, px, py, pz)

public:
    FourMomentum();
    explicit FourMomentum(double E, double px, double py, double pz);
    void validate() const;
    double getComponent(int index) const;
    double invariantMass() const;
    FourMomentum operator+(const FourMomentum& other) const;
    FourMomentum operator-(const FourMomentum& other) const;
    double operator*(const FourMomentum& other) const;
    FourMomentum& operator+=(const FourMomentum& other);
    bool operator!=(const FourMomentum& other) const;
    void adjustForPhysicalConsistency(double expectedMass);  // Adjust components for physical consistency
};

#endif // FOURMOMENTUM_H
