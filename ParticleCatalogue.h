#ifndef PARTICLE_CATALOGUE_H
#define PARTICLE_CATALOGUE_H

#include "Particle.h"
#include <vector>
#include <memory>
#include <iostream>

class ParticleCatalogue {
private:
    std::vector<std::shared_ptr<Particle>> particles;

public:
    // Add a particle to the catalogue
    void addParticle(const std::shared_ptr<Particle>& particle) {
        particles.push_back(particle);
    }

    // Remove all particles from the catalogue
    void clear() {
        particles.clear();
    }

    // Get the total number of particles
    size_t getTotalNumberOfParticles() const {
        return particles.size();
    }

    // Calculate the total four-momentum of all particles
    FourMomentum getTotalFourMomentum() const {
        FourMomentum totalMomentum;
        for (const auto& particle : particles) {
            totalMomentum += particle->getFourMomentum();
        }
        return totalMomentum;
    }

    // Print detailed information for each particle
    void printAllParticles(bool detailed = false) const {
        if (particles.empty()) {
            std::cout << "No particles in catalogue." << std::endl;
        } else {
            for (const auto& particle : particles) {
                particle->print(detailed);
            }
        }
    }

    // Get a vector of particles of a specific type
    std::vector<std::shared_ptr<Particle>> getParticlesByType(const std::string& type) const {
        std::vector<std::shared_ptr<Particle>> filteredParticles;
        for (const auto& particle : particles) {
            if (particle->getType() == type) {
                filteredParticles.push_back(particle);
            }
        }
        return filteredParticles;
    }
};

#endif // PARTICLE_CATALOGUE_H
