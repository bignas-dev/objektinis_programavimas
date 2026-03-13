#include "generator.h"
#include <fstream>
#include <iostream>
#include <random>
#include <iomanip>
#include <stdexcept>
#include <chrono>

GenerationResult measureFileGeneration(const std::string& filename, int recordCount) {
    auto start = std::chrono::high_resolution_clock::now();
    
    std::ofstream out(filename);
    if (!out.is_open()) {
        throw std::runtime_error("Nepavyko atidaryti failo rašymui: " + filename);
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 10);

    // Antraštė
    out << std::left << std::setw(20) << "Vardas" 
        << std::setw(20) << "Pavarde";
    for (int i = 1; i <= 5; ++i) {
        out << std::setw(10) << "ND" + std::to_string(i);
    }
    out << std::setw(10) << "Egz." << "\n";

    for (int i = 1; i <= recordCount; ++i) {
        out << std::left << std::setw(20) << ("VardasNR" + std::to_string(i))
            << std::setw(20) << ("PavardeNR" + std::to_string(i));
        
        for (int j = 0; j < 5; ++j) {
            out << std::setw(10) << dist(gen);
        }
        out << std::setw(10) << dist(gen) << "\n";
    }

    out.close();
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    
    GenerationResult res;
    res.count = recordCount;
    res.duration = diff.count();
    return res;
}
