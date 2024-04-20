#ifndef QUARK_H
#define QUARK_H

#include "Particle.h"
#include <iostream>

class Quark : public Particle {
protected:
    std::string type_;
    double charge_;
    double spin_;
    std::string colorCharge_;  // Added color charge for quarks
    FourMomentum fourMomentum_;

public:
    // Updated constructor to include color charge
    Quark(std::string type, double charge, double spin, std::string colorCharge, FourMomentum fourMomentum)
        : type_(type), charge_(charge), spin_(spin), colorCharge_(colorCharge), fourMomentum_(fourMomentum) {}

    virtual ~Quark() {}

    double charge() const override { return charge_; }
    double spin() const override { return spin_; }
    FourMomentum getFourMomentum() const override { return fourMomentum_; }
    std::string getType() const override { return type_; }

    // Added getter for color charge
    std::string getColorCharge() const { return colorCharge_; }

    void print(bool detailed) const override {
        std::cout << type_ << " with charge: " << charge_
                  << ", spin: " << spin_
                  << ", color charge: " << colorCharge_  // Display color charge
                  << ", four-momentum: E=" << fourMomentum_.getComponent(0)
                  << ", px=" << fourMomentum_.getComponent(1)
                  << ", py=" << fourMomentum_.getComponent(2)
                  << ", pz=" << fourMomentum_.getComponent(3)
                  << ", Derived Rest Mass: " << fourMomentum_.invariantMass() << " MeV"
                  << std::endl;
    }
};

#endif // QUARK_H
