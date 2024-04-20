#ifndef LEPTON_H
#define LEPTON_H

#include "Particle.h"
#include <iostream>
#include <vector>
#include <memory>

class Lepton : public Particle {
protected:
    double charge_;
    double spin_;
    int leptonNumber_;
    FourMomentum fourMomentum_;

public:
    Lepton(double charge, double spin, int leptonNumber, FourMomentum fourMomentum)
        : charge_(charge), spin_(spin), leptonNumber_(leptonNumber), fourMomentum_(fourMomentum) {}

    virtual ~Lepton() {}

    double charge() const override { return charge_; }
    double spin() const override { return spin_; }
    FourMomentum getFourMomentum() const override { return fourMomentum_; }
    virtual std::string getType() const override { return "Lepton"; }

    void print(bool detailed) const override {
        std::cout << getType() << " with charge: " << charge_
                  << ", spin: " << spin_
                  << ", lepton number: " << leptonNumber_;
        if (detailed) {
            std::cout << ", four-momentum: E=" << fourMomentum_.getComponent(0)
                      << ", px=" << fourMomentum_.getComponent(1)
                      << ", py=" << fourMomentum_.getComponent(2)
                      << ", pz=" << fourMomentum_.getComponent(3);
        }
        std::cout << std::endl;
    }
};

class Electron : public Lepton {
public:
    Electron(double charge, double spin, FourMomentum fourMomentum)
        : Lepton(charge, spin, (charge > 0 ? 1 : -1), fourMomentum) {}

    std::string getType() const override { return "Electron"; }
};

class Muon : public Lepton {
public:
    Muon(double charge, double spin, FourMomentum fourMomentum)
        : Lepton(charge, spin, (charge > 0 ? 1 : -1), fourMomentum) {}

    std::string getType() const override { return "Muon"; }
};

class Tau : public Lepton {
public:
    Tau(double charge, double spin, FourMomentum fourMomentum)
        : Lepton(charge, spin, (charge > 0 ? 1 : -1), fourMomentum) {}

    std::vector<std::shared_ptr<Particle>> decayProducts;

    void decay(const std::vector<std::shared_ptr<Particle>>& products) {
        decayProducts = products;
    }

    std::string getType() const override { return "Tau"; }

    void print(bool detailed) const override {
        Lepton::print(detailed);
        if (detailed && !decayProducts.empty()) {
            std::cout << " Decays into: ";
            for (auto& prod : decayProducts) {
                std::cout << prod->getType() << " ";
            }
        }
        std::cout << std::endl;
    }
};

#endif // LEPTON_H
