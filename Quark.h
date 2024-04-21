#ifndef QUARK_H
#define QUARK_H

#include "Particle.h"
#include <iostream>
#include <iomanip>  // For std::setprecision and std::fixed
#include <cmath>    // For std::fabs

class Quark : public Particle {
protected:
    std::string type_;
    double charge_;
    double spin_;
    std::string colorCharge_;  // Color charge for quarks
    FourMomentum fourMomentum_;

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

    // Getter for color charge
    std::string getColorCharge() const { return colorCharge_; }

    void validateMass() const {
        // Validate the mass based on expected quark masses (this is purely illustrative and not physically accurate)
        double expectedMass = getExpectedMass();
        double derivedMass = fourMomentum_.invariantMass();
        if (std::fabs(derivedMass - expectedMass) > 1e-3) {  // Allowing some tolerance
            std::cerr << "Warning: Mass discrepancy for " << type_
                      << ". Expected: " << expectedMass << " MeV, Derived: " << derivedMass << " MeV." << std::endl;
        }
    }

    double getExpectedMass() const {
        // Placeholder function for expected masses; these values are illustrative
        if (type_ == "Up" || type_ == "Anti-Up") return 2.3;
        if (type_ == "Down" || type_ == "Anti-Down") return 4.8;
        // Additional quark types can be added here
        return 0;
    }

    void print(bool detailed) const override {
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "----------------------------------------------------------------\n"
                  << "Particle Type  : " << getType() << "\n"
                  << "Charge         : " << charge() << "\n"
                  << "Spin           : " << spin() << "\n"
                  << "Color Charge   : " << getColorCharge() << "\n"
                  << "Four-momentum  : (E=" << getFourMomentum().getComponent(0)
                  << ", px=" << getFourMomentum().getComponent(1)
                  << ", py=" << getFourMomentum().getComponent(2)
                  << ", pz=" << getFourMomentum().getComponent(3) << ")\n"
                  << "Derived Mass   : " << fourMomentum_.invariantMass() << " MeV\n"
                  << "----------------------------------------------------------------\n";
    }
};

#endif // QUARK_H
