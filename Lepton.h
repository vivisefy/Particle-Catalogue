#ifndef LEPTON_H
#define LEPTON_H

#include "Particle.h"
#include <iostream>
#include <vector>
#include <memory>
#include <numeric>  // For std::accumulate
#include <iomanip>  // For std::setprecision

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
    virtual std::vector<std::shared_ptr<Particle>> decayProducts() const override {
        return {}; // Default: no decay products for generic leptons
    }

    void print(bool detailed) const override {
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "----------------------------------------------------------------\n"
                  << "Particle Type  : " << getType() << "\n"
                  << "Charge         : " << charge() << "\n"
                  << "Spin           : " << spin() << "\n"
                  << "Lepton Number  : " << leptonNumber_ << "\n"
                  << "Four-momentum  : (E=" << getFourMomentum().getComponent(0)
                  << ", px=" << getFourMomentum().getComponent(1)
                  << ", py=" << getFourMomentum().getComponent(2)
                  << ", pz=" << getFourMomentum().getComponent(3) << ")\n";
        if (detailed && !decayProducts().empty()) {
            std::cout << "Decays into    : ";
            for (const auto& prod : decayProducts()) {
                std::cout << prod->getType() << " ";
            }
            std::cout << "\n";
        }
        std::cout << "----------------------------------------------------------------\n";
    }
};

class Electron : public Lepton {
private:
    std::vector<double> calorimeterLayers;

public:
    Electron(double charge, double spin, FourMomentum fourMomentum, const std::vector<double>& layers)
        : Lepton(charge, spin, (charge > 0 ? 1 : -1), fourMomentum), calorimeterLayers(layers) {
        double totalCalorimeterEnergy = std::accumulate(layers.begin(), layers.end(), 0.0);
        if (std::abs(totalCalorimeterEnergy - fourMomentum_.getComponent(0)) > 1e-3) {  // Tightened tolerance
            std::cerr << "Warning: Total calorimeter energy does not match electron's energy (" 
                      << totalCalorimeterEnergy << " vs " << fourMomentum_.getComponent(0) << ")." << std::endl;
            // Adjust the energy component to match the sum of calorimeter layers.
            fourMomentum_.adjustForPhysicalConsistency(totalCalorimeterEnergy);
        }
    }

    std::string getType() const override { return "Electron"; }
};

class Muon : public Lepton {
private:
    bool isIsolated_;

public:
    Muon(double charge, double spin, FourMomentum fourMomentum, bool isolated)
        : Lepton(charge, spin, (charge > 0 ? 1 : -1), fourMomentum), isIsolated_(isolated) {}

    std::string getType() const override { return "Muon"; }
    bool isIsolated() const override { return isIsolated_; }
};

class Tau : public Lepton {
public:
    std::vector<std::shared_ptr<Particle>> decayProducts_;

    Tau(double charge, double spin, FourMomentum fourMomentum)
        : Lepton(charge, spin, (charge > 0 ? 1 : -1), fourMomentum) {}

    std::vector<std::shared_ptr<Particle>> decayProducts() const override {
        return decayProducts_; // Use the renamed variable
    }

    void setDecayProducts(const std::vector<std::shared_ptr<Particle>>& products) {
        decayProducts_ = products;
    }

    std::string getType() const override { return "Tau"; }

    void print(bool detailed) const override {
        Lepton::print(detailed);
        if (detailed && !decayProducts_.empty()) {
            std::cout << "Decays into    : ";
            for (auto& prod : decayProducts_) {
                std::cout << prod->getType() << " ";
            }
            std::cout << "\n";
        }
    }
};

class Neutrino : public Lepton {
public:
    Neutrino(double charge, double spin, int leptonNumber, FourMomentum fourMomentum)
        : Lepton(charge, spin, leptonNumber, fourMomentum) {}

    std::string getType() const override { return "Neutrino"; }

    void print(bool detailed) const override {
        Lepton::print(detailed);
    }
};

#endif // LEPTON_H