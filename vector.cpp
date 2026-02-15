#include <iomanip>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <ctime>

struct Mokinys {
    std::string vardas;
    std::string pavarde;
    std::vector<int> tarp_rez;
    int egz_rez;
    float galutinis;
};

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
    int count = rand() % 10 + 1;
    mokinys.tarp_rez.clear();
    for (int i = 0; i < count; ++i) {
        mokinys.tarp_rez.push_back(rand() % 11);
    }
    mokinys.egz_rez = rand() % 11;
    std::cout << "Sugeneruoti " << count << " namų darbų rezultatai";
    std::cout << " ir egzamino rezultatas: " << mokinys.egz_rez << "\n";
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

        if (std::cin.fail()) {
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
        std::cout << "Turite įvesti bent vieną tarpinį rezultatą.\n";
        exit(1);
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

void calculateFinalGrade(Mokinys &mokinys, const std::string& choice) {
    float tarp_rez;
    if (choice == "1") {
        tarp_rez = calculateAverage(mokinys.tarp_rez);
    } else {
        tarp_rez = calculateMedian(mokinys.tarp_rez);
    }
    mokinys.galutinis = 0.6f * mokinys.egz_rez + 0.4f * tarp_rez;
}

void displayResults(const std::vector<Mokinys>& students, const std::string& choice) {
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

    for (const auto& m : students) {
        std::cout << std::setw(langelio_ilgis) << m.pavarde
                  << std::setw(langelio_ilgis) << m.vardas
                  << std::setw(langelio_ilgis) << std::fixed << std::setprecision(2)
                  << m.galutinis << "\n";
    }
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    int input_mode;
    std::cout << "Pasirinkite įvesties būdą:\n"
              << "1 - Rankinis įvedimas\n"
              << "2 - Atsitiktinis generavimas\n"
              << "Jūsų pasirinkimas: ";
    std::cin >> input_mode;

    if (std::cin.fail() || (input_mode != 1 && input_mode != 2)) {
        std::cout << "Neteisinga įvestis: tinka '1' arba '2'.\n";
        return 1;
    }

    std::vector<Mokinys> students;

    while (true) {
        std::cout << "\nĮveskite " << students.size() + 1 << " studento duomenis:\n";
        Mokinys m;

        if (input_mode == 1) {
            readStudentData(m);
        } else {
            std::cout << "Įveskite vardą: ";
            std::cin >> m.vardas;
            std::cout << "Įveskite pavardę: ";
            std::cin >> m.pavarde;
            generateRandomGrades(m);
        }

        students.push_back(m);

        std::string ans;
        std::cout << "Ar norite įvesti dar vieną studentą? (t/n): ";
        std::cin >> ans;
        if (ans != "T" && ans != "t") {
            break;
        }
    }

    std::string choice;
    std::cout << "\nPasirinkite galutinio balo skaičiavimo būdą:\n"
              << "1 - Vidurkis\n"
              << "2 - Mediana\n"
              << "Jūsų pasirinkimas: ";
    std::cin >> choice;

    if (choice != "1" && choice != "2") {
        std::cout << "Neteisinga įvestis: tinka '1' arba '2'.\n";
        return 1;
    }

    for (auto& m : students) {
        calculateFinalGrade(m, choice);
    }

    displayResults(students, choice);

    return 0;
}
