#ifndef BOSON_H
#define BOSON_H

#include "Particle.h"
#include <iostream>
#include <vector>
#include <memory>
#include <iomanip>  // For std::setprecision and std::fixed

class Boson : public Particle {
protected:
    std::string type_;
    double charge_;
    double spin_;
    FourMomentum fourMomentum_;
    std::vector<std::shared_ptr<Particle>> decayProducts;  // Container for decay products

public:
    Boson(std::string type, double charge, double spin, FourMomentum fourMomentum)
        : type_(type), charge_(charge), spin_(spin), fourMomentum_(fourMomentum) {
        // Validate that the mass is correct for this type of particle
        validateMass();
    }

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
        std::cout << std::fixed << std::setprecision(2);  // Sets decimal precision for output
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

private:
    // Ensures that the calculated rest mass matches the expected mass for this boson type
    void validateMass() {
        const double tolerance = 1.0; // MeV tolerance for mass validation
        double expectedMass = getExpectedMassForType();
        if (std::fabs(fourMomentum_.invariantMass() - expectedMass) > tolerance) {
            std::cerr << "Warning: Inconsistent mass for " << type_
                      << ". Expected: " << expectedMass << " MeV, Found: " 
                      << fourMomentum_.invariantMass() << " MeV." << std::endl;
        }
    }

    double getExpectedMassForType() const {
        // These values should be updated according to the particle data group or similar reliable sources
        if (type_ == "W+") return 80379;
        if (type_ == "W-") return 80379;
        if (type_ == "Z0") return 91188;
        if (type_ == "Higgs") return 125100;
        return 0;  // Default for unknown types
    }
};

#endif // BOSON_H
