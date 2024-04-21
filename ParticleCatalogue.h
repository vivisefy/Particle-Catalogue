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
        particles.push_back(particle);
    }

    void clear() {
        particles.clear();
    }

    size_t getTotalNumberOfParticles() const {
        return particles.size();
    }

    FourMomentum getTotalFourMomentum() const {
        return std::accumulate(particles.begin(), particles.end(), FourMomentum(),
                               [](const FourMomentum& total, const std::shared_ptr<Particle>& p) {
                                   return total + p->getFourMomentum();
                               });
    }

    void printAllParticles(bool detailed = false) const {
        if (particles.empty()) {
            std::cout << "No particles in catalogue." << std::endl;
        } else {
            for (const auto& particle : particles) {
                particle->print(detailed);
            }
        }
    }

    template<typename ParticleType>
    std::vector<std::shared_ptr<Particle>> getParticlesByType() const {
        std::vector<std::shared_ptr<Particle>> filteredParticles;
        for (const auto& particle : particles) {
            if (typeid(*particle) == typeid(ParticleType)) {
                filteredParticles.push_back(particle);
            }
        }
        return filteredParticles;
    }

    std::unordered_map<std::string, int> getParticleTypeCounts() const {
        std::unordered_map<std::string, int> counts;
        for (const auto& particle : particles) {
            counts[typeid(*particle).name()]++;
        }
        return counts;
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
