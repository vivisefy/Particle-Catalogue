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
    
    auto muon = createParticle<Muon>(-1, 0.5, FourMomentum(105.7, 0, 0, 105.7), true);
    auto antimuon = createParticle<Muon>(1, 0.5, FourMomentum(105.7, 0, 0, -105.7), true);

    auto tau = createParticle<Tau>(-1, 0.5, FourMomentum(1776.86, 0, 0, 1776.86));
    auto antitau = createParticle<Tau>(1, 0.5, FourMomentum(1776.86, 0, 0, -1776.86));

    // Create neutrinos with small but non-zero momentum and correct lepton numbers
    auto neutrinoEnergy = 0.1; // Placeholder for demonstration; should be adjusted based on simulation needs
    auto electronNeutrino = createParticle<Neutrino>(0, 0.5, 1, FourMomentum(neutrinoEnergy, 0, 0, neutrinoEnergy));
    auto electronAntineutrino = createParticle<Neutrino>(0, 0.5, -1, FourMomentum(neutrinoEnergy, 0, 0, -neutrinoEnergy));

    // Create quarks with realistic four-momentum
    auto upQuark = createParticle<Quark>("Up", 2/3.0, 0.5, "Red", FourMomentum(2.3, 0, 0, 2.3));
    auto antiupQuark = createParticle<Quark>("Anti-Up", -2/3.0, 0.5, "Anti-Red", FourMomentum(2.3, 0, 0, -2.3));

    // Create gauge bosons with correct mass and energy matching momentum for massless photon
    auto photon = createParticle<Boson>("Photon", 0, 1, FourMomentum(10, 0, 0, 10)); // Example energy value for photon
    auto wPlus = createParticle<Boson>("W+", 1, 1, FourMomentum(80379, 0, 0, 0)); // 80379 MeV is the mass, no spatial momentum
    auto wMinus = createParticle<Boson>("W-", -1, 1, FourMomentum(80379, 0, 0, 0)); // Same as above
    auto zBoson = createParticle<Boson>("Z0", 0, 1, FourMomentum(91187.6, 0, 0, 0)); // Correctly reflecting mass

    // Create Higgs boson
    auto higgs = createParticle<Boson>("Higgs", 0, 0, FourMomentum(125100, 0, 0, 0)); // Mass of Higgs, no spatial momentum

    // Add particles to the catalogue
    catalogue.addParticle(electron);
    catalogue.addParticle(positron);
    catalogue.addParticle(muon);
    catalogue.addParticle(antimuon);
    catalogue.addParticle(tau);
    catalogue.addParticle(antitau);
    catalogue.addParticle(electronNeutrino);
    catalogue.addParticle(electronAntineutrino);
    catalogue.addParticle(photon);
    catalogue.addParticle(wPlus);
    catalogue.addParticle(wMinus);
    catalogue.addParticle(zBoson);
    catalogue.addParticle(higgs);

    // Display all particles
    std::cout << "All particles in the catalogue:" << std::endl;
    catalogue.printAllParticles(true);

    return 0;
}
