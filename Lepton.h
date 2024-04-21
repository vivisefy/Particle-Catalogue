#ifndef LEPTON_H
#define LEPTON_H

#include "Particle.h"
#include <iostream>
#include <vector>
#include <memory>
#include <numeric>  // For std::accumulate

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
    virtual std::vector<std::shared_ptr<Particle>> decay() const override {
        return {}; // Default: no decay products for generic leptons
    }

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
private:
    std::vector<double> calorimeterLayers;

public:
    Electron(double charge, double spin, FourMomentum fourMomentum, const std::vector<double>& layers)
        : Lepton(charge, spin, (charge > 0 ? 1 : -1), fourMomentum), calorimeterLayers(layers) {
        double totalCalorimeterEnergy = std::accumulate(layers.begin(), layers.end(), 0.0);
        if (totalCalorimeterEnergy != fourMomentum_.getComponent(0)) {
            std::cerr << "Warning: Total calorimeter energy does not match electron's energy." << std::endl;
            // Adjust the energy component to match the sum of calorimeter layers.
            fourMomentum_.adjustForPhysicalConsistency(totalCalorimeterEnergy);
        }
    }

    std::string getType() const override { return "Electron"; }
};

class Muon : public Lepton {
private:
    bool isIsolated;

public:
    Muon(double charge, double spin, FourMomentum fourMomentum, bool isolated)
        : Lepton(charge, spin, (charge > 0 ? 1 : -1), fourMomentum), isIsolated(isolated) {}

    std::string getType() const override { return "Muon"; }
};

class Tau : public Lepton {
public:
    std::vector<std::shared_ptr<Particle>> decayProducts;

    Tau(double charge, double spin, FourMomentum fourMomentum)
        : Lepton(charge, spin, (charge > 0 ? 1 : -1), fourMomentum) {}

    std::vector<std::shared_ptr<Particle>> decay() const override {
        // Example decay mechanism for a tau lepton
        return decayProducts; // This would be set by the simulation depending on the decay mode
    }

    void setDecayProducts(const std::vector<std::shared_ptr<Particle>>& products) {
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

class Neutrino : public Lepton {
public:
    Neutrino(double charge, double spin, int leptonNumber, FourMomentum fourMomentum)
        : Lepton(charge, spin, leptonNumber, fourMomentum) {}

    std::string getType() const override {
        return "Neutrino";
    }

    void print(bool detailed) const override {
        Lepton::print(detailed);
    }
};

#endif // LEPTON_H
