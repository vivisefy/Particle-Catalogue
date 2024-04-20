#ifndef UTILITIES_H
#define UTILITIES_H

#include <vector>
#include <memory>
#include <algorithm>

template<typename T>
bool checkParticleProperty(const std::vector<std::shared_ptr<T>>& particles, bool (*propFunc)(const T&)) {
    return std::all_of(particles.begin(), particles.end(), propFunc);
}

#endif // UTILITIES_H
