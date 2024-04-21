#ifndef PARTICLE_CATALOGUE_H
#define PARTICLE_CATALOGUE_H

#include "Particle.h"
#include <vector>
#include <memory>
#include <algorithm>
#include <typeinfo>
#include <unordered_map>
#include <iostream>
#include <functional>

class ParticleCatalogue {
private:
    std::vector<std::shared_ptr<Particle>> particles;

public:
    void addParticle(const std::shared_ptr<Particle>& particle) {
        if (particle) {
            particles.push_back(particle);
        } else {
            std::cerr << "Attempted to add a null particle to the catalogue." << std::endl;
        }
    }

    void clear() {
        particles.clear();
    }

    size_t getTotalNumberOfParticles() const {
        return particles.size();
    }

    FourMomentum getTotalFourMomentum() const {
        FourMomentum total;
        for (const auto& p : particles) {
            if (p) total += p->getFourMomentum();
        }
        return total;
    }

    std::unordered_map<std::string, int> getParticleCounts() const {
        std::unordered_map<std::string, int> counts;
        for (const auto& p : particles) {
            if (p) counts[p->getType()]++;
        }
        return counts;
    }

    void printParticleCounts() const {
        auto counts = getParticleCounts();
        std::cout << "Particle Counts:" << std::endl;
        for (const auto& count : counts) {
            std::cout << count.first << ": " << count.second << std::endl;
        }
    }

    void printAllParticles(bool detailed = false) const {
        std::cout << "\nAll particles in the catalogue:" << std::endl;
        if (particles.empty()) {
            std::cout << "No particles in catalogue." << std::endl;
        } else {
            printParticleCounts(); // Show summary counts first
            for (const auto& particle : particles) {
                if (particle) {
                    particle->print(detailed);
                }
            }
        }
    }

    template<typename ParticleType>
    std::vector<std::shared_ptr<Particle>> getParticlesByType() const {
        std::vector<std::shared_ptr<Particle>> filteredParticles;
        for (const auto& particle : particles) {
            if (particle && typeid(*particle) == typeid(ParticleType)) {
                filteredParticles.push_back(particle);
            }
        }
        return filteredParticles;
    }

    void sortParticles(const std::function<bool(const std::shared_ptr<Particle>&, const std::shared_ptr<Particle>&)>& comp) {
        std::sort(particles.begin(), particles.end(), comp);
    }

    std::vector<std::shared_ptr<Particle>> filterParticles(const std::function<bool(const std::shared_ptr<Particle>&)>& pred) const {
        std::vector<std::shared_ptr<Particle>> result;
        std::copy_if(particles.begin(), particles.end(), std::back_inserter(result), pred);
        return result;
    }
};

#endif // PARTICLE_CATALOGUE_H
