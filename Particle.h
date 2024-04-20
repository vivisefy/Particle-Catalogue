#ifndef PARTICLE_H
#define PARTICLE_H

#include <string>
#include "FourMomentum.h"

class Particle {
public:
    virtual ~Particle() {}

    virtual double charge() const = 0;
    virtual double spin() const = 0;
    virtual void print(bool detailed) const = 0;  // Updated signature
    virtual std::string getType() const = 0;
    virtual FourMomentum getFourMomentum() const = 0;  // Ensure this is correctly implemented in derived classes
};

#endif // PARTICLE_H
