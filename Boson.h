#include "Particle.h"
#include <iostream>
#include <vector>
#include <memory>

class Boson : public Particle {
protected:
    std::string type_;
    double charge_;
    double spin_;
    FourMomentum fourMomentum_;

public:
    Boson(std::string type, double charge, double spin, FourMomentum fourMomentum)
        : type_(type), charge_(charge), spin_(spin), fourMomentum_(fourMomentum) {}

    virtual ~Boson() {}

    double charge() const override { return charge_; }
    double spin() const override { return spin_; }
    FourMomentum getFourMomentum() const override { return fourMomentum_; }
    std::string getType() const override { return type_; }

    void print(bool detailed) const override {
        std::cout << type_ << " with charge: " << charge_
                  << ", spin: " << spin_
                  << ", four-momentum: E=" << fourMomentum_.getComponent(0)
                  << ", px=" << fourMomentum_.getComponent(1)
                  << ", py=" << fourMomentum_.getComponent(2)
                  << ", pz=" << fourMomentum_.getComponent(3)
                  << ", Derived Rest Mass: " << fourMomentum_.invariantMass() << " MeV"
                  << std::endl;
    }
};
