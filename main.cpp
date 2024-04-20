#include <iostream>
#include <memory>
#include "ParticleCatalogue.h"
#include "Lepton.h"
#include "Quark.h"
#include "Boson.h"
#include "FourMomentum.h"

void testParticles() {
    ParticleCatalogue<std::vector<std::shared_ptr<Particle>>> catalogue;

    // Adding specific leptons
    catalogue.addParticle(std::make_shared<Electron>(-1, 0.5, FourMomentum(0.511, 0, 0, 0))); // Electron
    catalogue.addParticle(std::make_shared<Muon>(-1, 0.5, FourMomentum(105.66, 0, 0, 0))); // Muon
    catalogue.addParticle(std::make_shared<Tau>(-1, 0.5, FourMomentum(1776.86, 0, 0, 0))); // Tau

    // Adding quarks with corrected baryon numbers
    catalogue.addParticle(std::make_shared<Quark>(2/3.0, 0.5, FourMomentum(1.275, 0, 0, 0))); // Up quark
    catalogue.addParticle(std::make_shared<Quark>(-1/3.0, 0.5, FourMomentum(4.18, 0, 0, 0))); // Down quark

    // Adding bosons
    catalogue.addParticle(std::make_shared<Boson>(0, 1, FourMomentum(91.1876, 0, 0, 0))); // Z boson
    catalogue.addParticle(std::make_shared<Boson>(+1, 1, FourMomentum(80.379, 0, 0, 0))); // W+ boson
    catalogue.addParticle(std::make_shared<Boson>(-1, 1, FourMomentum(80.379, 0, 0, 0))); // W- boson

    // Printing all particles with detailed information
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
