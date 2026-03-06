#include "mokinys.h"
#include "utils.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <stdexcept>

float calculateAverage(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += arr[i];
    }
    return static_cast<float>(sum) / static_cast<float>(size);
}

float calculateMedian(int arr[], int size) {
    int* temp = new int[size];
    for (int i = 0; i < size; ++i) {
        temp[i] = arr[i];
    }

    std::sort(temp, temp + size);

    float result;
    if (size % 2 == 0) {
        result = (temp[size/2 - 1] + temp[size/2]) / 2.;
    } else {
        result = static_cast<float>(temp[size/2]);
    }
    delete[] temp;
    return result;
}

void generateRandomGrades(Mokinys& mokinys) {
    mokinys.tarp_count = rand() % 10 + 1;
    mokinys.tarp_rez = new int[mokinys.tarp_count];

    for (int i = 0; i < mokinys.tarp_count; i++) {
        mokinys.tarp_rez[i] = rand() % 11;
    }

    mokinys.egz_rez = rand() % 11;
}

void readStudentData(Mokinys& mokinys) {
    std::cout << "Įveskite vardą: ";
    std::cin >> mokinys.vardas;
    std::cout << "Įveskite pavardę: ";
    std::cin >> mokinys.pavarde;

    int capacity = 2;
    int count = 0;
    int* grades = new int[capacity];

    while (true) {
        std::cout << "Įveskite " << count + 1 << " tarpinį rezultatą (arba -1, jei baigėte): ";
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
        if (count == capacity) {
            capacity *= 2;
            int* new_grades = new int[capacity];
            for (int i = 0; i < count; ++i) {
                new_grades[i] = grades[i];
            }
            delete[] grades;
            grades = new_grades;
        }
        grades[count] = grade;
        count++;
    }

    try {
        if (count == 0) {
            throw std::runtime_error("Turite įvesti bent vieną tarpinį rezultatą.\n");
        }
    } catch (const std::runtime_error& e) {
        std::cout << e.what();
        throw;
    }

    int* final_grades = new int[count];
    for (int i = 0; i < count; ++i) {
        final_grades[i] = grades[i];
    }
    delete[] grades;
    mokinys.tarp_rez = final_grades;
    mokinys.tarp_count = count;

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

void calculateFinalGrade(Mokinys& mokinys, const std::string& choice) {
    float tarp_rez;
    if (choice == "1") {
        tarp_rez = calculateAverage(mokinys.tarp_rez, mokinys.tarp_count);
    } else {
        tarp_rez = calculateMedian(mokinys.tarp_rez, mokinys.tarp_count);
    }
    mokinys.galutinis = 0.6 * mokinys.egz_rez + 0.4 * tarp_rez;
}

void displayResults(Mokinys* students[], int count, const std::string& choice) {
    const int langelio_ilgis = 20;

    std::cout << "\n" << std::setw(langelio_ilgis) << "Pavardė"
              << std::setw(langelio_ilgis) << "Vardas";

    if (choice == "1") {
        std::cout << std::setw(langelio_ilgis) << "Galutinis (Vid.)";
    } else {
        std::cout << std::setw(langelio_ilgis) << "Galutinis (Med.)";
    }
    std::cout << "\n";

    std::cout << std::setfill('-') << std::setw(langelio_ilgis * 3) << ""
              << std::setfill(' ') << "\n";

    for (int i = 0; i < count; ++i) {
        std::cout << std::setw(langelio_ilgis) << students[i]->pavarde
                  << std::setw(langelio_ilgis) << students[i]->vardas
                  << std::setw(langelio_ilgis) << std::fixed << std::setprecision(2)
                  << students[i]->galutinis << "\n";
    }
}
