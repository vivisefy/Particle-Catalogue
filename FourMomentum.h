#ifndef FOURMOMENTUM_H
#define FOURMOMENTUM_H

#include <vector>
#include <cmath>
#include <stdexcept>

class FourMomentum {
private:
    std::vector<double> components;

public:
    FourMomentum();
    FourMomentum(double E, double px, double py, double pz);
    void validate() const;
    double getComponent(int index) const;
    double invariantMass() const;
    FourMomentum operator+(const FourMomentum& other) const;
    FourMomentum operator-(const FourMomentum& other) const;
    double operator*(const FourMomentum& other) const;
    FourMomentum& operator+=(const FourMomentum& other);
    bool operator!=(const FourMomentum& other) const;
};

#endif // FOURMOMENTUM_H
