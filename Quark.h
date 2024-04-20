#ifndef QUARK_H
#define QUARK_H

#include "Particle.h"
#include <iostream>

class Quark : public Particle {
protected:
    double charge_;
    double spin_;
    double baryonNumber_;
    FourMomentum fourMomentum_;

public:
    Quark(double charge, double spin, FourMomentum fourMomentum)
        : charge_(charge), spin_(spin), fourMomentum_(fourMomentum) {
        // Calculate the baryon number based on the charge
        baryonNumber_ = (charge == 2/3.0 || charge == -2/3.0) ? 1.0/3 : -1.0/3;
    }
    
    virtual ~Quark() {}

    double charge() const override { return charge_; }
    double spin() const override { return spin_; }
    double getBaryonNumber() const { return baryonNumber_; } // Getter for baryon number
    FourMomentum getFourMomentum() const override { return fourMomentum_; }
    std::string getType() const override { return "Quark"; }

    void print(bool detailed) const override {
        std::cout << "Quark with charge: " << charge_
                  << ", spin: " << spin_
                  << ", baryon number: " << baryonNumber_
                  << ", four-momentum: E=" << fourMomentum_.getComponent(0)
                  << ", px=" << fourMomentum_.getComponent(1)
                  << ", py=" << fourMomentum_.getComponent(2)
                  << ", pz=" << fourMomentum_.getComponent(3)
                  << ", Derived Rest Mass: " << fourMomentum_.invariantMass() << " MeV"
                  << std::endl;
    }
};

#endif // QUARK_H
