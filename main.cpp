#include "Particle.h"
#include "Lepton.h"
#include "Quark.h"
#include "Boson.h"
#include "FourMomentum.h"
#include "ParticleCatalogue.h"
#include <memory>
#include <iostream>
#include <vector>

// Factory function for particle creation
template<typename ParticleType, typename... Args>
std::shared_ptr<Particle> createParticle(Args&&... args) {
    return std::make_shared<ParticleType>(std::forward<Args>(args)...);
}

int main() {
    ParticleCatalogue catalogue;

    // Correctly initialize electrons and positrons with matching calorimeter energy
    auto electron = createParticle<Electron>(-1, 0.5, FourMomentum(0.5, 0, 0, 0), std::vector<double>{0.125, 0.125, 0.125, 0.125});
    auto positron = createParticle<Electron>(1, 0.5, FourMomentum(0.5, 0, 0, 0), std::vector<double>{0.125, 0.125, 0.125, 0.125});
    catalogue.addParticle(electron);
    catalogue.addParticle(positron);

    // Demonstrating input validation for muons with physically impossible four-momentum
    try {
        auto invalidMuon = createParticle<Muon>(-1, 0.5, FourMomentum(10, 0, 0, 50), true);
        catalogue.addParticle(invalidMuon);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error creating muon: " << e.what() << '\n';
        // Correct the four-momentum and create the muon
        auto correctedMuon = createParticle<Muon>(-1, 0.5, FourMomentum(51, 0, 0, 50), true);
        catalogue.addParticle(correctedMuon);
        std::cout << "Muon created with corrected four-momentum.\n";
    }

    // Initialize and add tau leptons
    auto tau = createParticle<Tau>(-1, 0.5, FourMomentum(1776.86, 0, 0, 1776.86));
    auto antitau = createParticle<Tau>(1, 0.5, FourMomentum(1776.86, 0, 0, -1776.86));
    catalogue.addParticle(tau);
    catalogue.addParticle(antitau);

    // Create neutrinos with small but non-zero momentum and correct lepton numbers
    auto neutrinoEnergy = 0.1; // Placeholder for demonstration; should be adjusted based on simulation needs
    auto electronNeutrino = createParticle<Neutrino>(0, 0.5, 1, FourMomentum(neutrinoEnergy, 0, 0, neutrinoEnergy));
    auto electronAntineutrino = createParticle<Neutrino>(0, 0.5, -1, FourMomentum(neutrinoEnergy, 0, 0, -neutrinoEnergy));
    catalogue.addParticle(electronNeutrino);
    catalogue.addParticle(electronAntineutrino);

    // Create quarks with realistic four-momentum
    auto upQuark = createParticle<Quark>("Up", 2/3.0, 0.5, "Red", FourMomentum(2.3, 0, 0, 2.3));
    auto antiupQuark = createParticle<Quark>("Anti-Up", -2/3.0, 0.5, "Anti-Red", FourMomentum(2.3, 0, 0, -2.3));
    catalogue.addParticle(upQuark);
    catalogue.addParticle(antiupQuark);

    // Create gauge bosons with correct mass and energy matching momentum for massless photon
    auto photon = createParticle<Boson>("Photon", 0, 1, FourMomentum(10, 0, 0, 10)); // Example energy value for photon
    auto wPlus = createParticle<Boson>("W+", 1, 1, FourMomentum(80379, 0, 0, 0)); // 80379 MeV is the mass, no spatial momentum
    auto wMinus = createParticle<Boson>("W-", -1, 1, FourMomentum(80379, 0, 0, 0)); // Same as above
    auto zBoson = createParticle<Boson>("Z0", 0, 1, FourMomentum(91187.6, 0, 0, 0)); // Correctly reflecting mass
    auto higgs = createParticle<Boson>("Higgs", 0, 0, FourMomentum(125100, 0, 0, 0)); // Mass of Higgs, no spatial momentum
    catalogue.addParticle(photon);
    catalogue.addParticle(wPlus);
    catalogue.addParticle(wMinus);
    catalogue.addParticle(zBoson);
    catalogue.addParticle(higgs);

    // Adding decay products for Tau to demonstrate handling unstable particles
    std::shared_ptr<Particle> pion = createParticle<Lepton>(-1, 0, 1, FourMomentum(139.57, 0, 0, 100)); // Example pion
    std::shared_ptr<Particle> neutrino = createParticle<Neutrino>(0, 0.5, 1, FourMomentum(0.1, 0, 0, 0.1));
    dynamic_cast<Tau*>(tau.get())->setDecayProducts({pion, neutrino});

    // Display all particles, using detailed output to show full properties and any decay products
    std::cout << "All particles in the catalogue:\n";
    catalogue.printAllParticles(true);

    return 0;
}
