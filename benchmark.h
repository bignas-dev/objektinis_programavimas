#ifndef BENCHMARK_H
#define BENCHMARK_H

#include "student.h"
#include <string>
#include <vector>

struct GenerationResult {
    int count;
    double duration;
};

struct BenchmarkResult {
    std::string containerType;
    int strategy;
    int recordCount;
    double readDuration;
    double sortDuration;
    double splitDuration;
    double writeDuration;
    double totalDuration;
};

GenerationResult measureFileGeneration(const std::string& filename, int recordCount);

BenchmarkResult runBenchmarkVector(const std::string& filename, int strategy, const std::string& gradeType);
BenchmarkResult runBenchmarkList(const std::string& filename, int strategy, const std::string& gradeType);
BenchmarkResult runBenchmarkDeque(const std::string& filename, int strategy, const std::string& gradeType);

void writeResultsToCSV(const std::string& filename, const std::vector<BenchmarkResult>& results);
void printResultsTable(const std::vector<BenchmarkResult>& results);

#endif
