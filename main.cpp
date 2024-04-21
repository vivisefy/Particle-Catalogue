#include "Particle.h"
#include "Quark.h"
#include "FourMomentum.h"
#include "ParticleCatalogue.h"
#include <memory>
#include <iostream>
#include <vector>
#include <cmath> // Needed for sqrt function

// Factory function for particle creation
template<typename ParticleType, typename... Args>
std::shared_ptr<Particle> createParticle(Args&&... args) {
    return std::make_shared<ParticleType>(std::forward<Args>(args)...);
}

int main() {
    ParticleCatalogue catalogue;

    // Function to calculate total energy from mass and momentum
    auto calculateEnergy = [](double mass, double px, double py, double pz) {
        return sqrt(mass*mass + px*px + py*py + pz*pz);
    };

    // Create quarks with realistic four-momentum and various color charges
    double upMass = 2.3;
    double downMass = 4.8;
    double charmMass = 1275.0;
    double pz = 2.3; // Common pz for illustration, adjust as necessary for each particle

    auto upQuarkRed = createParticle<Quark>("Up", 2/3.0, 0.5, "Red", FourMomentum(calculateEnergy(upMass, 0, 0, pz), 0, 0, pz));
    auto antiupQuarkAntiRed = createParticle<Quark>("Anti-Up", -2/3.0, 0.5, "Anti-Red", FourMomentum(calculateEnergy(upMass, 0, 0, -pz), 0, 0, -pz));
    auto downQuarkBlue = createParticle<Quark>("Down", -1/3.0, 0.5, "Blue", FourMomentum(calculateEnergy(downMass, 0, 0, pz), 0, 0, pz));
    auto antidownQuarkAntiBlue = createParticle<Quark>("Anti-Down", 1/3.0, 0.5, "Anti-Blue", FourMomentum(calculateEnergy(downMass, 0, 0, -pz), 0, 0, -pz));
    auto charmQuarkGreen = createParticle<Quark>("Charm", 2/3.0, 0.5, "Green", FourMomentum(calculateEnergy(charmMass, 0, 0, pz), 0, 0, pz));
    auto anticharmQuarkAntiGreen = createParticle<Quark>("Anti-Charm", -2/3.0, 0.5, "Anti-Green", FourMomentum(calculateEnergy(charmMass, 0, 0, -pz), 0, 0, -pz));

    catalogue.addParticle(upQuarkRed);
    catalogue.addParticle(antiupQuarkAntiRed);
    catalogue.addParticle(downQuarkBlue);
    catalogue.addParticle(antidownQuarkAntiBlue);
    catalogue.addParticle(charmQuarkGreen);
    catalogue.addParticle(anticharmQuarkAntiGreen);

    // Display all quarks in the catalogue, using detailed output to show full properties
    std::cout << "All quarks in the catalogue:\n";
    catalogue.printAllParticles(true);  // Assuming printAllParticles(bool detailed) is implemented to handle the detailed flag

    return 0;
}
