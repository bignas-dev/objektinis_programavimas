#include "student.h"
#include "utils.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <chrono>

float calculateAverage(const std::vector<int>& arr) {
    if (arr.empty()) return 0.0f;
    int sum = 0;
    for (int val : arr) {
        sum += val;
    }
    return static_cast<float>(sum) / static_cast<float>(arr.size());
}

float calculateMedian(std::vector<int> arr) {   
    if (arr.empty()) return 0.0f;
    std::sort(arr.begin(), arr.end());
    size_t size = arr.size();
    if (size % 2 == 0) {
        return (arr[size/2 - 1] + arr[size/2]) / 2.0f;
    } else {
        return static_cast<float>(arr[size/2]);
    }
}

void generateRandomGrades(Mokinys& mokinys) {
    int tarp_count = rand() % 10 + 1; 
    mokinys.tarp_rez.reserve(tarp_count);
    for (int i = 0; i < tarp_count; ++i) {
        mokinys.tarp_rez.push_back(rand() % 11); 
    }
    mokinys.egz_rez = rand() % 11;
}

void readStudentData(Mokinys& mokinys) {
    std::cout << "Įveskite vardą: ";
    std::cin >> mokinys.vardas;
    std::cout << "Įveskite pavardę: ";
    std::cin >> mokinys.pavarde;

    while (true) {
        std::cout << "Įveskite " << mokinys.tarp_rez.size() + 1
                  << " tarpinį rezultatą (arba -1, jei baigėte): ";
        int grade;
        if (!(std::cin >> grade)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Neteisinga įvestis. Bandykite dar kartą.\n";
            continue;
        }

        if (grade == -1) {
            break;
        }
        if (grade < 0 || grade > 10) {
            std::cout << "Rezultatas turi būti nuo 0 iki 10. Bandykite dar kartą.\n";
            continue;
        }
        mokinys.tarp_rez.push_back(grade);
    }

    if (mokinys.tarp_rez.empty()) {
        std::cout << "Turite įvesti bent vieną tarpinį rezultatą. Generuojami atsitiktiniai.\n";
        generateRandomGrades(mokinys);
    }

    std::cout << "Įveskite egzamino rezultatą: ";
    while (!(std::cin >> mokinys.egz_rez) || mokinys.egz_rez < 0 || mokinys.egz_rez > 10) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Neteisinga įvestis (0-10). Bandykite dar kartą: ";
    }
}

std::vector<Mokinys> readFromFile(const std::string& filename) {
    std::vector<Mokinys> students;
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Klaida: nepavyko atidaryti failo " + filename);
    }

    std::string line;
    std::getline(file, line); // Praleidžiame antraštę

    while (std::getline(file, line)) {
        if (line.empty()) continue; 

        std::istringstream iss(line);
        Mokinys m;
        if (!(iss >> m.vardas >> m.pavarde)) continue;

        int grade;
        for (int i = 0; i < 5; ++i) {
            if (iss >> grade) {
                m.tarp_rez.push_back(grade);
            }
        }
        iss >> m.egz_rez;
        students.push_back(m);
    }

    file.close();
    return students;
}

void calculateFinalGrade(Mokinys& mokinys, const std::string& choice) {
    float tarp_rez;
    if (choice == "1") {
        tarp_rez = calculateAverage(mokinys.tarp_rez);
    } else {
        tarp_rez = calculateMedian(mokinys.tarp_rez);
    }
    mokinys.galutinis = 0.6f * mokinys.egz_rez + 0.4f * tarp_rez;
}

void displayResults(const std::vector<Mokinys>& students, const std::string& choice) { 
    std::ostream& out = std::cout;
    const int langelio_ilgis = 20;
    std::string kategorija = (choice == "1") ? "Galutinis (Vid.)" : "Galutinis (Med.)";

    out << std::left;  
    out << std::setw(langelio_ilgis) << "Pavardė"
        << std::setw(langelio_ilgis) << "Vardas"
        << std::setw(langelio_ilgis) << kategorija << '\n';
    out << std::string(3 * langelio_ilgis, '-') << '\n';

    for (const auto& m : students) {
        out << std::setw(langelio_ilgis) << m.pavarde
            << std::setw(langelio_ilgis) << m.vardas
            << std::setw(langelio_ilgis) << std::fixed << std::setprecision(2) << m.galutinis
            << '\n';
    }
}

ProcessingResult runProcessingTest(const std::string& filename, const std::string& gradeType) {
    auto total_start = std::chrono::high_resolution_clock::now();
    
    // 1. Nuskaitymas
    auto read_start = std::chrono::high_resolution_clock::now();
    std::vector<Mokinys> students = readFromFile(filename);
    auto read_end = std::chrono::high_resolution_clock::now();
    
    // 2. Rūšiavimas į kategorijas
    auto sort_start = std::chrono::high_resolution_clock::now();
    for (auto& s : students) {
        calculateFinalGrade(s, gradeType);
    }
    
    std::vector<Mokinys> vargsiukai;
    std::vector<Mokinys> kietiakiai;
    
    for (const auto& s : students) {
        if (s.galutinis < 5.0f) {
            vargsiukai.push_back(s);
        } else {
            kietiakiai.push_back(s);
        }
    }
    auto sort_end = std::chrono::high_resolution_clock::now();
    
    // 3. Išvedimas
    auto write_start = std::chrono::high_resolution_clock::now();
    auto write_to_file = [&](const std::string& fname, const std::vector<Mokinys>& list) {
        std::ofstream out(fname);
        out << std::left << std::setw(20) << "Vardas" << std::setw(20) << "Pavarde" << "Galutinis\n";
        for (const auto& s : list) {
            out << std::left << std::setw(20) << s.vardas << std::setw(20) << s.pavarde 
                << std::fixed << std::setprecision(2) << s.galutinis << "\n";
        }
        out.close();
    };
    
    write_to_file("vargšiukai.txt", vargsiukai);
    write_to_file("kietiakai.txt", kietiakiai);
    auto write_end = std::chrono::high_resolution_clock::now();
    
    auto total_end = std::chrono::high_resolution_clock::now();
    
    ProcessingResult res;
    res.readDuration = std::chrono::duration<double>(read_end - read_start).count();
    res.sortDuration = std::chrono::duration<double>(sort_end - sort_start).count();
    res.writeDuration = std::chrono::duration<double>(write_end - write_start).count();
    res.totalDuration = std::chrono::duration<double>(total_end - total_start).count();
    
    return res;
}
