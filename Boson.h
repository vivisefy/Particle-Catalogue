#ifndef BOSON_H
#define BOSON_H

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
    std::vector<std::shared_ptr<Particle>> decayProducts;  // Container for decay products

public:
    Boson(std::string type, double charge, double spin, FourMomentum fourMomentum)
        : type_(type), charge_(charge), spin_(spin), fourMomentum_(fourMomentum) {}

    virtual ~Boson() {}

    double charge() const override { return charge_; }
    double spin() const override { return spin_; }
    FourMomentum getFourMomentum() const override { return fourMomentum_; }
    std::string getType() const override { return type_; }

    // Manage decay products
    void addDecayProduct(const std::shared_ptr<Particle>& particle) {
        decayProducts.push_back(particle);
    }

    void clearDecayProducts() {
        decayProducts.clear();
    }

    const std::vector<std::shared_ptr<Particle>>& getDecayProducts() const {
        return decayProducts;
    }

    void print(bool detailed) const override {
        std::cout << type_ << " with charge: " << charge_
                  << ", spin: " << spin_
                  << ", four-momentum: E=" << fourMomentum_.getComponent(0)
                  << ", px=" << fourMomentum_.getComponent(1)
                  << ", py=" << fourMomentum_.getComponent(2)
                  << ", pz=" << fourMomentum_.getComponent(3)
                  << ", Derived Rest Mass: " << fourMomentum_.invariantMass() << " MeV";
        if (detailed && !decayProducts.empty()) {
            std::cout << ", Decays into: ";
            for (const auto& prod : decayProducts) {
                std::cout << prod->getType() << " ";
            }
        }
        std::cout << std::endl;
    }
};

#endif // BOSON_H
