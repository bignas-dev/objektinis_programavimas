#include "benchmark.h"
#include <iostream>
#include <iomanip>
#include <vector>

int main() {
    std::vector<int> sizes = {1000, 10000, 100000, 1000000, 10000000};
    std::vector<std::string> size_names = {"1k", "10k", "100k", "1M", "10M"};
    std::string gradeType = "1";
    
    std::cout << "Pradedami v1.0 spartos tyrimai...\n";
    std::cout << "Tiriami konteineriai: vector, list, deque\n";
    std::cout << "Strategijos: 1 (du nauji konteineriai), 2 (vienas naujas + trynimas), 3 (std::partition)\n";
    std::cout << "Iš viso bus atlikta: " << sizes.size() * 3 * 3 << " tyrimų\n\n";
    
    std::vector<BenchmarkResult> allResults;
    allResults.reserve(45);
    
    for (size_t i = 0; i < sizes.size(); ++i) {
        std::string filename = "studentai_" + size_names[i] + ".txt";
        std::cout << "=== " << size_names[i] << " (" << sizes[i] << " irasu) ===\n";
        std::cout << "Generuojamas failas...\n";
        GenerationResult gen = measureFileGeneration(filename, sizes[i]);
        std::cout << "Failo generavimo laikas: " << std::fixed << std::setprecision(4) << gen.duration << " s\n\n";
        
        for (int strategy = 1; strategy <= 3; ++strategy) {
            std::cout << "Strategija " << strategy << " (vector): " << std::flush;
            BenchmarkResult resVec = runBenchmarkVector(filename, strategy, gradeType);
            resVec.recordCount = sizes[i];
            allResults.push_back(resVec);
            std::cout << "baigta\n";
            
            std::cout << "Strategija " << strategy << " (list): " << std::flush;
            BenchmarkResult resList = runBenchmarkList(filename, strategy, gradeType);
            resList.recordCount = sizes[i];
            allResults.push_back(resList);
            std::cout << "baigta\n";
            
            std::cout << "Strategija " << strategy << " (deque): " << std::flush;
            BenchmarkResult resDeque = runBenchmarkDeque(filename, strategy, gradeType);
            resDeque.recordCount = sizes[i];
            allResults.push_back(resDeque);
            std::cout << "baigta\n";
        }
        std::cout << "\n";
    }
    
    std::cout << "\n=== VISI REZULTATAI ===\n";
    printResultsTable(allResults);
    printContainerComparison(allResults);
    
    writeResultsToCSV("rezultatai.csv", allResults);
    std::cout << "\nRezultatai issaugoti i 'rezultatai.csv'\n";
    
    std::cout << "\nTyrimai baigti.\n";
    std::cout << "Rezultatai išsaugoti faile: rezultatai.csv\n";
    return 0;
}
