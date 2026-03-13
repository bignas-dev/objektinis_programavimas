#include "student.h"
#include "generator.h"
#include <iostream>
#include <vector>
#include <iomanip>

void printResults(const std::string& size, GenerationResult gen, ProcessingResult proc) {
    std::cout << "\nFailo dydis: " << size << "\n";
    std::cout << "--------------------------------------\n";
    std::cout << std::left << std::setw(30) << "Veiksmas" << "Laikas (s)\n";
    std::cout << std::string(45, '-') << "\n";
    std::cout << std::setw(30) << "Failo generavimas (1 tyrimas)" << gen.duration << "\n";
    std::cout << std::setw(30) << "Nuskaitymas iš failo" << proc.readDuration << "\n";
    std::cout << std::setw(30) << "Rūšiavimas į kategorijas" << proc.sortDuration << "\n";
    std::cout << std::setw(30) << "Išvedimas į du failus" << proc.writeDuration << "\n";
    std::cout << std::setw(30) << "Bendra programa (2 tyrimas)" << proc.totalDuration << "\n";
}

int main() {
    std::vector<int> sizes = {1000, 10000, 100000, 1000000, 10000000};
    std::vector<std::string> size_names = {"1k", "10k", "100k", "1M", "10M"};

    std::cout << "Pradedami v0.4 spartos tyrimai...\n";

    for (size_t i = 0; i < sizes.size(); ++i) {
        std::string filename = "studentai_" + size_names[i] + ".txt";
        
        // 1 tyrimas: kūrimas
        GenerationResult gen = measureFileGeneration(filename, sizes[i]);
        
        // 2 tyrimas: apdorojimas (naudoja jau sukurtą failą)
        ProcessingResult proc = runProcessingTest(filename, "1"); // Naudojame vidurkį
        
        printResults(size_names[i], gen, proc);
    }

    std::cout << "\nTyrimai baigti.\n";
    return 0;
}
