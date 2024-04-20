#ifndef LEPTON_H
#define LEPTON_H

#include "Particle.h"
#include <iostream>

class Lepton : public Particle {
private:
    double charge_;  // Lepton charge
    double spin_;    // Lepton spin
    int leptonNumber_;    // +1 for particles, -1 for antiparticles
    FourMomentum fourMomentum_;

public:
    Lepton(double charge, double spin, int leptonNumber, FourMomentum fourMomentum)
        : charge_(charge), spin_(spin), leptonNumber_(leptonNumber), fourMomentum_(fourMomentum) {}

    virtual ~Lepton() {}

    double charge() const override { return charge_; }
    double spin() const override { return spin_; }
    FourMomentum getFourMomentum() const override { return fourMomentum_; }
    std::string getType() const override { return "Lepton"; }

    void print(bool detailed) const override {
        std::cout << "Lepton with charge: " << charge_
                  << ", spin: " << spin_
                  << ", lepton number: " << leptonNumber_;
        if (detailed) {
            // Print detailed information including four-momentum
            std::cout << ", four-momentum: E=" << fourMomentum_.getComponent(0)
                      << ", px=" << fourMomentum_.getComponent(1)
                      << ", py=" << fourMomentum_.getComponent(2)
                      << ", pz=" << fourMomentum_.getComponent(3);
        }
        std::cout << std::endl;
    }
};

#endif // LEPTON_H
