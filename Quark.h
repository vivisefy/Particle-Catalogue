#ifndef QUARK_H
#define QUARK_H

#include "Particle.h"
#include <iostream>

class Quark : public Particle {
private:
    double charge_;
    double spin_;
    int baryonNumber_;
    FourMomentum fourMomentum_;

public:
    Quark(double charge, double spin, int baryonNumber, FourMomentum fourMomentum)
        : charge_(charge), spin_(spin), baryonNumber_(baryonNumber), fourMomentum_(fourMomentum) {}

    virtual ~Quark() {}

    double charge() const override { return charge_; }
    double spin() const override { return spin_; }
    FourMomentum getFourMomentum() const override { return fourMomentum_; }
    std::string getType() const override { return "Quark"; }

    void print(bool detailed) const override {
        std::cout << "Quark with charge: " << charge_
                  << ", spin: " << spin_
                  << ", baryon number: " << baryonNumber_;
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

#endif // QUARK_H
