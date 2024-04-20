#ifndef PARTICLECATALOGUE_H
#define PARTICLECATALOGUE_H

#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>
#include "Particle.h"

// Utilizing template to allow for flexible container types
template <typename Container = std::vector<std::shared_ptr<Particle>>>
class ParticleCatalogue {
private:
    Container particles;  // Container for storing shared pointers to particles

public:
    // Adds a particle to the catalogue
    void addParticle(const std::shared_ptr<Particle>& particle) {
        particles.push_back(particle);
    }

    // Prints all particles in the catalogue
    void printAllParticles(bool detailed = false) const {
        for (const auto& particle : particles) {
            particle->print(detailed);
        }
    }

    // Calculates and returns the total four-momentum of all particles in the catalogue
    FourMomentum totalFourMomentum() const {
        FourMomentum total(0, 0, 0, 0);
        for (const auto& particle : particles) {
            total += particle->getFourMomentum();  // Using operator+= for clarity
        }
        return total;
    }

    // Returns a new ParticleCatalogue containing only particles with the specified charge
    ParticleCatalogue<Container> filterByCharge(double charge) const {
        ParticleCatalogue<Container> filteredCatalogue;
        std::copy_if(particles.begin(), particles.end(), std::back_inserter(filteredCatalogue.particles),
                     [charge](const std::shared_ptr<Particle>& p) { return p->charge() == charge; });
        return filteredCatalogue;
    }

    // Returns the number of particles in the catalogue
    size_t size() const {
        return particles.size();
    }

    // Provides iterator access to the underlying container
    auto begin() -> decltype(particles.begin()) {
        return particles.begin();
    }

    auto end() -> decltype(particles.end()) {
        return particles.end();
    }
};

#endif // PARTICLECATALOGUE_H
