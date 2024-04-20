#ifndef BOSON_H
#define BOSON_H

#include "Particle.h"
#include <iostream>
#include <vector>
#include <memory>

class Boson : public Particle {
private:
    double charge_;             // Boson charge
    double spin_;               // Boson spin
    FourMomentum fourMomentum_; // Boson four-momentum

public:
    // Constructor with initialization list
    Boson(double charge, double spin, FourMomentum fourMomentum)
        : charge_(charge), spin_(spin), fourMomentum_(fourMomentum) {}

    // Destructor
    virtual ~Boson() override {}

    // Overridden methods from Particle
    double charge() const override {
        return charge_; // Return the charge of the Boson
    }

    double spin() const override {
        return spin_; // Return the spin of the Boson
    }

    std::string getType() const override {
        return "Boson"; // Return the type as a string
    }

    FourMomentum getFourMomentum() const override {
        return fourMomentum_; // Return the four-momentum
    }

    void print(bool detailed) const override {
        // Print the basic information
        std::cout << getType() << " with charge: " << charge()
                  << " and spin: " << spin();

        // If detailed is true, print the four-momentum components
        if (detailed) {
            std::cout << ", Four-Momentum: E=" << fourMomentum_.getComponent(0)
                      << ", px=" << fourMomentum_.getComponent(1)
                      << ", py=" << fourMomentum_.getComponent(2)
                      << ", pz=" << fourMomentum_.getComponent(3);
        }
        std::cout << std::endl;
    }
};

#endif // BOSON_H
