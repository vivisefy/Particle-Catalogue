#ifndef PARTICLE_H
#define PARTICLE_H

#include <iostream>  // For std::cout and std::endl
#include <string>
#include "FourMomentum.h"

class Particle {
public:
    virtual ~Particle() {}

    virtual double charge() const = 0;
    virtual double spin() const = 0;
    virtual void print(bool detailed) const = 0;
    virtual std::string getType() const = 0;
    virtual FourMomentum getFourMomentum() const = 0;

    virtual int getBaryonNumber() const { return 0; }
    virtual int getLeptonNumber() const { return 0; }
    virtual bool isStable() const { return true; }

    void displayBasicInfo() const {
        std::cout << getType() << ":\n"
                  << "  Charge: " << charge() << "\n"
                  << "  Spin: " << spin() << "\n"
                  << "  Four-momentum: E=" << getFourMomentum().getComponent(0)
                  << ", px=" << getFourMomentum().getComponent(1)
                  << ", py=" << getFourMomentum().getComponent(2)
                  << ", pz=" << getFourMomentum().getComponent(3) << "\n"
                  << "  Baryon Number: " << getBaryonNumber() << "\n"
                  << "  Lepton Number: " << getLeptonNumber() << "\n"
                  << "  Stability: " << (isStable() ? "Stable" : "Unstable") << std::endl;
    }
};

#endif // PARTICLE_H
