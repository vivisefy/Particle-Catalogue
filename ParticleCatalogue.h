#ifndef PARTICLECATALOGUE_H
#define PARTICLECATALOGUE_H

#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>
#include "Particle.h"

template <typename Container = std::vector<std::shared_ptr<Particle>>>
class ParticleCatalogue {
private:
    Container particles;

public:
    void addParticle(const std::shared_ptr<Particle>& particle) {
        particles.push_back(particle);
    }

    void printAllParticles(bool detailed = false) const {
        for (const auto& particle : particles) {
            particle->print(detailed);
        }
    }

    FourMomentum totalFourMomentum() const {
        FourMomentum total(0, 0, 0, 0);
        for (const auto& particle : particles) {
            total = total + particle->getFourMomentum();
        }
        return total;
    }

    ParticleCatalogue<Container> filterByCharge(double charge) const {
        ParticleCatalogue<Container> filteredCatalogue;
        std::copy_if(particles.begin(), particles.end(), std::back_inserter(filteredCatalogue.particles),
                     [charge](const std::shared_ptr<Particle>& p) { return p->charge() == charge; });
        return filteredCatalogue;
    }

    size_t size() const {
        return particles.size();
    }

    auto begin() -> decltype(particles.begin()) {
        return particles.begin();
    }

    auto end() -> decltype(particles.end()) {
        return particles.end();
    }
};

#endif // PARTICLECATALOGUE_H
