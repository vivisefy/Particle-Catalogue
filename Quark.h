#ifndef QUARK_H
#define QUARK_H

#include "Particle.h"
#include <iostream>
#include <iomanip>  // For std::setprecision and std::fixed
#include <cmath>    // For std::fabs
#include <vector>
#include <memory>   // For std::shared_ptr

class Quark : public Particle {
protected:
    std::string type_;
    double charge_;
    double spin_;
    std::string colorCharge_;  // Color charge for quarks
    FourMomentum fourMomentum_;
    std::vector<std::shared_ptr<Particle>> decayProducts_; // Store decay products

public:
    // Constructor to initialize quark properties including color charge
    Quark(const std::string& type, double charge, double spin, const std::string& colorCharge, const FourMomentum& fourMomentum)
        : type_(type), charge_(charge), spin_(spin), colorCharge_(colorCharge), fourMomentum_(fourMomentum) {
        validateMass();
    }

    virtual ~Quark() {}

    double charge() const override { return charge_; }
    double spin() const override { return spin_; }
    FourMomentum getFourMomentum() const override { return fourMomentum_; }
    std::string getType() const override { return type_; }

    // Getter and setter for color charge
    std::string getColorCharge() const { return colorCharge_; }
    void setColorCharge(const std::string& colorCharge) { colorCharge_ = colorCharge; }

    // Methods to handle decay products
    void addDecayProduct(const std::shared_ptr<Particle>& particle) {
        decayProducts_.push_back(particle);
    }

    // Display decay paths
    void printDecayProducts() const {
        if (decayProducts_.empty()) {
            std::cout << "No decay products listed.\n";
        } else {
            std::cout << "Decays into:\n";
            for (const auto& p : decayProducts_) {
                p->print(false); // Minimal details
            }
        }
    }

    // Validate the mass based on expected quark masses
    void validateMass() const {
        double expectedMass = getExpectedMass();
        double derivedMass = fourMomentum_.invariantMass();
        if (std::fabs(derivedMass - expectedMass) > 1e-3) {  // Allowing some tolerance
            std::cerr << "Warning: Mass discrepancy for " << type_
                      << ". Expected: " << expectedMass << " MeV, Derived: " << derivedMass << " MeV." << std::endl;
        }
    }

    double getExpectedMass() const {
        // Quark masses are generally averages or ranges, these are approximate mid-values.
        if (type_ == "Up" || type_ == "Anti-Up") return 2.3;
        if (type_ == "Down" || type_ == "Anti-Down") return 4.8;
        if (type_ == "Charm" || type_ == "Anti-Charm") return 1275;
        if (type_ == "Strange" || type_ == "Anti-Strange") return 95;
        if (type_ == "Top" || type_ == "Anti-Top") return 173000;
        if (type_ == "Bottom" || type_ == "Anti-Bottom") return 4180;
        return 0; // Should never be reached; ensures every quark type has a corresponding mass
    }

    // Extended print function to include decay products
    void print(bool detailed) const override {
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Particle Type  : " << getType() << "\n"
                  << "Charge         : " << std::setprecision(3) << charge() << "\n"
                  << "Spin           : " << spin() << "\n"
                  << "Color Charge   : " << colorCharge_ << "\n"
                  << "Four-momentum  : (E=" << getFourMomentum().getComponent(0)
                  << ", px=" << getFourMomentum().getComponent(1)
                  << ", py=" << getFourMomentum().getComponent(2)
                  << ", pz=" << getFourMomentum().getComponent(3) << ")\n";
        if (detailed) {
            printDecayProducts();
        }
    }
};

#endif // QUARK_H
