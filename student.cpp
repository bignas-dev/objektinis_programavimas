#include "student.h"
#include "utils.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>

float calculateAverage(const std::vector<int>& arr) {
    int sum = 0;
    for (int val : arr) {
        sum += val;
    }
    return static_cast<float>(sum) / static_cast<float>(arr.size());
}

float calculateMedian(std::vector<int> arr) {   
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
        std::cin >> grade;

        try {
            std::cin >> grade;
            if (std::cin.fail()) {
                throw std::runtime_error("Neteisinga įvestis. Bandykite dar kartą.\n");
            }
            if (grade == -1) {
                break;
            }
            if (grade < 0 || grade > 10) {
                throw std::runtime_error("Rezultatas turi būti nuo 0 iki 10. Bandykite dar kartą.\n");
            }
        } catch (const std::runtime_error& e) {
            std::cout << e.what();
            continue;
        }
        mokinys.tarp_rez.push_back(grade);
    }

    try {
        if (mokinys.tarp_rez.empty()) {
            throw std::runtime_error("Turite įvesti bent vieną tarpinį rezultatą.\n");
        }
    } catch (const std::runtime_error& e) {
        std::cout << e.what();
        throw;
    }

    std::cout << "Įveskite egzamino rezultatą: ";
    try {
        std::cin >> mokinys.egz_rez;
        if (std::cin.fail()) {
            throw std::runtime_error("Neteisinga įvestis: privalote įvesti sveikąjį skaičių.\n");
        }
        if (mokinys.egz_rez < 0 || mokinys.egz_rez > 10) {
            throw std::runtime_error("Neteisinga įvestis: egzamino rezultatas turi būti nuo 0 iki 10.\n");
        }
    } catch (const std::runtime_error& e) {
        std::cout << e.what();
        throw;
    }
}

std::vector<Mokinys> readFromFile(const std::string& filename) {
    std::vector<Mokinys> students;
    std::ifstream file(filename);
    try {
        if (!file.is_open()) {
            throw std::runtime_error("Klaida: nepavyko atidaryti failo " + filename + "\n");
        }
    } catch (const std::runtime_error& e) {
        std::cerr << e.what();
        throw;
    }

    std::string line;
    std::getline(file, line);

    int lineNum = 1;
    while (std::getline(file, line)) {
        lineNum++;
        if (line.empty()) continue; 

        std::istringstream iss(line);
        Mokinys m;
        iss >> m.vardas >> m.pavarde;

        int grade;
        for (int i = 0; i < 5; ++i) {
            try {
                if (!(iss >> grade)) {
                    std::string err = "Klaida faile " + filename + ", eilutėje " + std::to_string(lineNum)
                              + ": trūksta namų darbų pažymių.\n";
                    throw std::runtime_error(err);
                }
                if (grade < 0 || grade > 10) {
                    std::string err = "Klaida faile " + filename + ", eilutėje " + std::to_string(lineNum)
                              + ": pažymys " + std::to_string(grade) + " neleistinas (turi būti 0-10).\n";
                    throw std::runtime_error(err);
                }
            } catch (const std::runtime_error& e) {
                std::cerr << e.what();
                throw;
            }
            m.tarp_rez.push_back(grade);
        }

        try {
            if (!(iss >> m.egz_rez)) {
                std::string err = "Klaida faile " + filename + ", eilutėje " + std::to_string(lineNum)
                          + ": trūksta egzamino rezultato.\n";
                throw std::runtime_error(err);
            }
            if (m.egz_rez < 0 || m.egz_rez > 10) {
                std::string err = "Klaida faile " + filename + ", eilutėje " + std::to_string(lineNum)
                          + ": egzamino rezultatas " + std::to_string(m.egz_rez) + " neleistinas (turi būti 0-10).\n";
                throw std::runtime_error(err);
            }
        } catch (const std::runtime_error& e) {
            std::cerr << e.what();
            throw;
        }

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
    const int langelio_ilgis = 30;
    std::string kategorija = (choice == "1") ? "Galutinis (Vid.)" : "Galutinis (Med.)";

    auto old_precision = out.precision();
    auto old_flags = out.flags();

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

    out.flags(old_flags);
    out.precision(old_precision);
}
