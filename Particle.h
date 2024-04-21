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

    // Enhanced decay mechanism to allow more flexible handling of decays
    virtual std::vector<std::shared_ptr<Particle>> decayProducts() const {
        return {}; // By default, an empty vector (no decay products)
    }

    // Virtual functions for properties specific to certain types of particles
    virtual bool isIsolated() const { return false; } // For muons
    virtual bool hasInteracted() const { return false; } // For neutrinos

    // Utility function to display basic information about the particle
    void displayBasicInfo() const {
        std::cout << std::fixed << std::setprecision(2); // Sets decimal precision for output
        std::cout << "----------------------------------------------------------------\n"
                  << "Particle Information\n"
                  << "----------------------------------------------------------------\n"
                  << "Type       : " << getType() << "\n"
                  << "Charge     : " << charge() << "\n"
                  << "Spin       : " << spin() << "\n"
                  << "Momentum   : (E=" << getFourMomentum().getComponent(0)
                  << ", px=" << getFourMomentum().getComponent(1)
                  << ", py=" << getFourMomentum().getComponent(2)
                  << ", pz=" << getFourMomentum().getComponent(3) << ")\n"
                  << "Baryon No. : " << getBaryonNumber() << "\n"
                  << "Lepton No. : " << getLeptonNumber() << "\n"
                  << "Stability  : " << (isStable() ? "Stable" : "Unstable") << "\n"
                  << "----------------------------------------------------------------\n";
    }
};

#endif // PARTICLE_H
