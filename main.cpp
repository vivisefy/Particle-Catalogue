#include <iostream>
#include <memory>
#include "ParticleCatalogue.h"
#include "Lepton.h"
#include "Quark.h"
#include "Boson.h"
#include "FourMomentum.h"

void testParticles() {
    ParticleCatalogue<std::vector<std::shared_ptr<Particle>>> catalogue;

    // Adding leptons including neutrinos
    std::vector<double> electronLayers{100, 200, 300, 400}; // Example layer energies for calorimeter
    catalogue.addParticle(std::make_shared<Electron>(-1, 0.5, FourMomentum(1000, 0, 0, 0), electronLayers));
    catalogue.addParticle(std::make_shared<Electron>(1, 0.5, FourMomentum(1000, 0, 0, 0), electronLayers)); // Positron
    catalogue.addParticle(std::make_shared<Muon>(-1, 0.5, FourMomentum(105.66, 0, 0, 0), true));
    catalogue.addParticle(std::make_shared<Muon>(1, 0.5, FourMomentum(105.66, 0, 0, 0), true)); // Anti-muon
    catalogue.addParticle(std::make_shared<Tau>(-1, 0.5, FourMomentum(1776.86, 0, 0, 0)));
    catalogue.addParticle(std::make_shared<Tau>(1, 0.5, FourMomentum(1776.86, 0, 0, 0))); // Anti-tau
    catalogue.addParticle(std::make_shared<Neutrino>(0, 0.5, FourMomentum(0, 0, 0, 0), "Electron Neutrino"));
    catalogue.addParticle(std::make_shared<Neutrino>(0, 0.5, FourMomentum(0, 0, 0, 0), "Muon Neutrino"));
    catalogue.addParticle(std::make_shared<Neutrino>(0, 0.5, FourMomentum(0, 0, 0, 0), "Tau Neutrino"));

    // Adding quarks
    catalogue.addParticle(std::make_shared<Quark>("Up Quark", 2/3.0, 0.5, FourMomentum(2.3, 0, 0, 0)));
    catalogue.addParticle(std::make_shared<Quark>("Anti-Up Quark", -2/3.0, 0.5, FourMomentum(2.3, 0, 0, 0)));
    catalogue.addParticle(std::make_shared<Quark>("Down Quark", -1/3.0, 0.5, FourMomentum(4.8, 0, 0, 0)));
    catalogue.addParticle(std::make_shared<Quark>("Anti-Down Quark", 1/3.0, 0.5, FourMomentum(4.8, 0, 0, 0)));
    catalogue.addParticle(std::make_shared<Quark>("Charm Quark", 2/3.0, 0.5, FourMomentum(1.27, 0, 0, 0)));
    catalogue.addParticle(std::make_shared<Quark>("Anti-Charm Quark", -2/3.0, 0.5, FourMomentum(1.27, 0, 0, 0)));
    catalogue.addParticle(std::make_shared<Quark>("Strange Quark", -1/3.0, 0.5, FourMomentum(0.095, 0, 0, 0)));
    catalogue.addParticle(std::make_shared<Quark>("Anti-Strange Quark", 1/3.0, 0.5, FourMomentum(0.095, 0, 0, 0)));
    catalogue.addParticle(std::make_shared<Quark>("Top Quark", 2/3.0, 0.5, FourMomentum(173.1, 0, 0, 0)));
    catalogue.addParticle(std::make_shared<Quark>("Anti-Top Quark", -2/3.0, 0.5, FourMomentum(173.1, 0, 0, 0)));
    catalogue.addParticle(std::make_shared<Quark>("Bottom Quark", -1/3.0, 0.5, FourMomentum(4.18, 0, 0, 0)));
    catalogue.addParticle(std::make_shared<Quark>("Anti-Bottom Quark", 1/3.0, 0.5, FourMomentum(4.18, 0, 0, 0)));

    // Adding bosons
    catalogue.addParticle(std::make_shared<Boson>("Z Boson", 0, 1, FourMomentum(91.1876, 0, 0, 0)));
    catalogue.addParticle(std::make_shared<Boson>("W+ Boson", 1, 1, FourMomentum(80.379, 0, 0, 0)));
    catalogue.addParticle(std::make_shared<Boson>("W- Boson", -1, 1, FourMomentum(80.379, 0, 0, 0)));
    catalogue.addParticle(std::make_shared<Boson>("Higgs Boson", 0, 0, FourMomentum(125.10, 0, 0, 0)));
    catalogue.addParticle(std::make_shared<Boson>("Photon", 0, 1, FourMomentum(0, 0, 0, 0)));

    // Print all particles
    std::cout << "All particles added successfully and their details are:" << std::endl;
    catalogue.printAllParticles(true);
}

int main() {
    try {
        testParticles();
    } catch (const std::exception& e) {
        std::cerr << "Exception caught in main: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "Program completed successfully." << std::endl;
    return 0;
}
