#include <iostream>
#include <memory>
#include <vector>
#include "ParticleCatalogue.h"
#include "Lepton.h"
#include "Quark.h"
#include "Boson.h"
#include "FourMomentum.h"

void testParticles() {
    ParticleCatalogue<std::vector<std::shared_ptr<Particle>>> catalogue;

    try {
        catalogue.addParticle(std::make_shared<Lepton>(-1, 0.5, 1, FourMomentum(0.511, 0, 0, 0))); // Electron
        catalogue.addParticle(std::make_shared<Quark>(2/3.0, 0.5, 1, FourMomentum(1.275, 0, 0, 0))); // Up quark
        catalogue.addParticle(std::make_shared<Boson>(0, 1, FourMomentum(91.1876, 0, 0, 0))); // Z boson
    } catch (const std::invalid_argument& e) {
        std::cerr << "Failed to add particle: " << e.what() << std::endl;
    }

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
