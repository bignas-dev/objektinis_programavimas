#include <iomanip>
#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>

struct Mokinys {
    std::string vardas;
    std::string pavarde;
    int tarp_rez[3];
    int egz_rez;
    float galutinis;
};

float calculateAverage(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return static_cast<float>(sum) / static_cast<float>(size);
}

float calculateMedian(int arr[], int size) {
    int temp[3];
    for (int i = 0; i < size; i++) {
        temp[i] = arr[i];
    }
    std::sort(temp, temp + size);
    
    if (size % 2 == 0) {
        return (temp[size/2 - 1] + temp[size/2]) / 2.0f;
    } else {
        return static_cast<float>(temp[size/2]);
    }
}

void readStudentData(Mokinys& mokinys, int tarp_count) {
    std::cout << "Įveskite vardą: ";
    std::cin >> mokinys.vardas;

    std::cout << "Įveskite pavardę: ";
    std::cin >> mokinys.pavarde;

    for (int i = 0; i < tarp_count; i++) {
        std::cout << "Įveskite " << i + 1 << " tarpinį rezultatą: ";
        std::cin >> mokinys.tarp_rez[i];

        if (std::cin.fail()) {
            std::cout << "Neteisinga įvestis: privalote įvesti sveikąjį skaičių.\n";
            exit(1);
        }

        if (mokinys.tarp_rez[i] < 0 || mokinys.tarp_rez[i] > 10) {
            std::cout << "Neteisinga įvestis: rezultatas turi būti nuo 0 iki 10.\n";
            exit(1);
        }
    }

    std::cout << "Įveskite egzamino rezultatą: ";
    std::cin >> mokinys.egz_rez;

    if (std::cin.fail()) {
        std::cout << "Neteisinga įvestis: privalote įvesti sveikąjį skaičių.\n";
        exit(1);
    }

    if (mokinys.egz_rez < 0 || mokinys.egz_rez > 10) {
        std::cout << "Neteisinga įvestis: egzamino rezultatas turi būti nuo 0 iki 10.\n";
        exit(1);
    }
}

void calculateFinalGrade(Mokinys &mokinys, std::string choice) {
    float tarp_rez;
    if (choice == "1") {
        tarp_rez = calculateAverage(mokinys.tarp_rez, 3);
    } else {
        tarp_rez = calculateMedian(mokinys.tarp_rez, 3);
    }
    mokinys.galutinis = 0.6f * mokinys.egz_rez + 0.4f * tarp_rez;
}

void displayResults(Mokinys students[], int count, std::string choice) {
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

    for (int i = 0; i < count; i++) {
        std::cout << std::setw(langelio_ilgis) << students[i].pavarde
                  << std::setw(langelio_ilgis) << students[i].vardas
                  << std::setw(langelio_ilgis) << std::fixed << std::setprecision(2) 
                  << students[i].galutinis << "\n";
    }
}

int main() {
    int n, m;
    std::cout << "Iveskite namu darbu skaiciu: ";
    std::cin >> n;

    if (std::cin.fail()) {
        std::cout << "Neteisinga įvestis: privalote įvesti sveikaji skaičių.\n";
        return 1;
    }

    if (n < 0) {
        std::cout << "Neteisinga įvestis: rezultatas turi būti daugiau nei 0.\n";
        return 1;
    }

    std::cout << "Iveskite studentu skaiciu: ";
    std::cin >> m;

    if (std::cin.fail()) {
        std::cout << "Neteisinga įvestis: privalote įvesti sveikaji skaičių.\n";
        return 1;
    }

    if (m < 0) {
        std::cout << "Neteisinga įvestis: rezultatas turi būti daugiau nei 0.\n";
        return 1;
    }

    Mokinys students[m];
    
    std::string choice;
    std::cout << "Pasirinkite galutinio balo skaičiavimo būdą:\n"
              << "1 - Vidurkis\n"
              << "2 - Mediana\n"
              << "Jūsų pasirinkimas: ";
    std::cin >> choice;

    if (choice != "1" && choice != "2") {
        std::cout << "Neteisinga įvestis: tinka '1' arba '2', gauta '" << choice << "'\n";
        return 1;
    }

    for (int i = 0; i < m; i++) {
        std::cout << "\n" << i + 1 << " studento duomenys:\n";
        readStudentData(students[i], n);
        calculateFinalGrade(students[i], choice);
    }

    displayResults(students, m, choice);

    return 0;
}
