#ifndef PARTICLE_H
#define PARTICLE_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <iomanip> // For std::setprecision and std::fixed
#include "FourMomentum.h"

class Particle {
public:
    // Virtual destructor to ensure derived class destructors are called
    virtual ~Particle() {}

    // Pure virtual functions defining the interface that all derived classes must implement
    virtual double charge() const = 0;
    virtual double spin() const = 0;
    virtual void print(bool detailed) const = 0;
    virtual std::string getType() const = 0;
    virtual FourMomentum getFourMomentum() const = 0;

    // Optional virtual functions for quantum numbers and stability
    virtual int getBaryonNumber() const { return 0; }
    virtual int getLeptonNumber() const { return 0; }
    virtual bool isStable() const { return true; }

    // Virtual function for decay, returning a vector of decay products
    virtual std::vector<std::shared_ptr<Particle>> decay() const {
        return {}; // By default, an empty vector (no decay products)
    }

    // Utility function to display basic information about the particle
    void displayBasicInfo() const {
        std::cout << std::fixed << std::setprecision(2); // Sets decimal precision for output
        std::cout << "Particle type: " << getType() << "\n"
                  << "Charge: " << charge() << "\n"
                  << "Spin: " << spin() << "\n"
                  << "Four-momentum: E=" << getFourMomentum().getComponent(0)
                  << ", px=" << getFourMomentum().getComponent(1)
                  << ", py=" << getFourMomentum().getComponent(2)
                  << ", pz=" << getFourMomentum().getComponent(3) << "\n"
                  << "Baryon Number: " << getBaryonNumber() << "\n"
                  << "Lepton Number: " << getLeptonNumber() << "\n"
                  << "Stability: " << (isStable() ? "Stable" : "Unstable") << std::endl;
    }
};

#endif // PARTICLE_H
