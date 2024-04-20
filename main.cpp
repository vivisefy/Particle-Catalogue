#include "Particle.h"
#include "Lepton.h"
#include "Quark.h"
#include "Boson.h"
#include "FourMomentum.h"
#include "ParticleCatalogue.h"
#include <memory>
#include <iostream>

int main() {
    // Create particle catalogue
    ParticleCatalogue catalogue;

    // Define some four-momentum examples
    FourMomentum p1(100, 0, 0, 100); // Electron
    FourMomentum p2(80, 0, 0, 80);   // Muon
    FourMomentum p3(120, 10, 0, 0);  // Quark

    // Create some particles
    std::shared_ptr<Particle> electron(new Electron(-1, 0.5, p1, std::vector<double>{20, 20, 30, 30}));
    std::shared_ptr<Particle> muon(new Muon(-1, 0.5, p2, true));
    std::shared_ptr<Particle> quark(new Quark("Up", 2/3, 0.5, "Red", p3));

    // Add particles to catalogue
    catalogue.addParticle(electron);
    catalogue.addParticle(muon);
    catalogue.addParticle(quark);

    // Print all particles
    std::cout << "All particles in the catalogue:" << std::endl;
    catalogue.printAllParticles(true);

    // Calculate and print the total four-momentum
    FourMomentum totalMomentum = catalogue.getTotalFourMomentum();
    std::cout << "Total Four-Momentum: E=" << totalMomentum.getComponent(0)
              << ", px=" << totalMomentum.getComponent(1)
              << ", py=" << totalMomentum.getComponent(2)
              << ", pz=" << totalMomentum.getComponent(3) << std::endl;

    return 0;
}
