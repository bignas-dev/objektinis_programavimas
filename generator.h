#ifndef GENERATOR_H
#define GENERATOR_H

#include <string>
#include <chrono>

struct GenerationResult {
    int count;
    double duration;
};

GenerationResult measureFileGeneration(const std::string& filename, int recordCount);

#endif
