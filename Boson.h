#ifndef BOSON_H
#define BOSON_H

#include "Particle.h"
#include <iostream>
#include <vector>
#include <memory>
#include <iomanip>  // For std::setprecision and std::fixed
#include <cmath>    // For std::fabs

class Boson : public Particle {
protected:
    std::string type_;
    double charge_;
    double spin_;
    FourMomentum fourMomentum_;
    std::vector<std::shared_ptr<Particle>> decayProducts;  // Container for decay products

public:
    Boson(const std::string& type, double charge, double spin, const FourMomentum& fourMomentum)
        : type_(type), charge_(charge), spin_(spin), fourMomentum_(fourMomentum) {
        validateMass(); // Validate the mass at construction
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
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "----------------------------------------------------------------\n"
                  << "Particle Type  : " << getType() << "\n"
                  << "Charge         : " << charge() << "\n"
                  << "Spin           : " << spin() << "\n"
                  << "Four-momentum  : (E=" << getFourMomentum().getComponent(0)
                  << ", px=" << getFourMomentum().getComponent(1)
                  << ", py=" << getFourMomentum().getComponent(2)
                  << ", pz=" << getFourMomentum().getComponent(3) << ")\n"
                  << "Derived Mass   : " << fourMomentum_.invariantMass() << " MeV\n";
        if (detailed && !decayProducts.empty()) {
            std::cout << "Decays into    : ";
            for (const auto& prod : decayProducts) {
                std::cout << prod->getType() << " (" << prod->getFourMomentum().invariantMass() << " MeV) ";
            }
            std::cout << "\n";
        }
        std::cout << "----------------------------------------------------------------\n";
    }

private:
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
