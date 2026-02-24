#include <iomanip>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>   
#include <sstream>   

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

        if (std::cin.fail()) {
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


std::vector<Mokinys> readFromFile(const std::string& filename) {
    std::vector<Mokinys> students;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Klaida: nepavyko atidaryti failo " << filename << std::endl;
        return students; 
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
            if (!(iss >> grade)) {
                std::cerr << "Klaida faile " << filename << ", eilutėje " << lineNum
                          << ": trūksta namų darbų pažymių." << std::endl;
                return students;
            }
            if (grade < 0 || grade > 10) {
                std::cerr << "Klaida faile " << filename << ", eilutėje " << lineNum
                          << ": pažymys " << grade << " neleistinas (turi būti 0-10)." << std::endl;
                return students;
            }
            m.tarp_rez.push_back(grade);
        }

        
        if (!(iss >> m.egz_rez)) {
            std::cerr << "Klaida faile " << filename << ", eilutėje " << lineNum
                      << ": trūksta egzamino rezultato." << std::endl;
            return students;
        }
        if (m.egz_rez < 0 || m.egz_rez > 10) {
            std::cerr << "Klaida faile " << filename << ", eilutėje " << lineNum
                      << ": egzamino rezultatas " << m.egz_rez << " neleistinas (turi būti 0-10)." << std::endl;
            return students;
        }

        students.push_back(m);
    }

    file.close();
    return students;
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

void displayResults(const std::vector<Mokinys>& students, const std::string& choice)  {
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

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    const std::string vardai[] = {"Jonas", "Petras", "Antanas", "Kazys", "Linas",
                                   "Marius", "Tomas", "Andrius", "Darius", "Gediminas"};
    const std::string pavardes[] = {"Jonaitis", "Petraitis", "Antanaitis", "Kazlauskas", "Lingys",
                                     "Mariūnas", "Tomauskas", "Andriulis", "Dargis", "Gedminas"};
    int vardu_kiekis = sizeof(vardai) / sizeof(vardai[0]);
    int pavardziu_kiekis = sizeof(pavardes) / sizeof(pavardes[0]);

    int input_mode;
    std::cout << "Pasirinkite įvesties būdą:\n"
              << "1 - Rankinis įvedimas\n"
              << "2 - Atsitiktinis generavimas\n"
              << "3 - Nuskaitymas iš failo (kursiokai.txt)\n"
              << "Jūsų pasirinkimas: ";
    std::cin >> input_mode;

    if (std::cin.fail() || input_mode < 1 || input_mode > 3) {
        std::cout << "Neteisinga įvestis: tinka '1', '2' arba '3'.\n";
        return 1;
    }

    std::vector<Mokinys> students;

    if (input_mode == 1) {
        
        while (true) {
            std::cout << "\nĮveskite " << students.size() + 1 << " studento duomenis:\n";
            Mokinys m;
            readStudentData(m);
            students.push_back(m);

            std::string ans;
            std::cout << "Ar norite įvesti dar vieną studentą? (t/n): ";
            std::cin >> ans;
            if (ans != "T" && ans != "t") {
                break;
            }
        }
    }
    else if (input_mode == 2) {
        while (true) {
            std::cout << "\nĮveskite " << students.size() + 1 << " studento duomenis:\n";
            Mokinys m;
            m.vardas = vardai[rand() % vardu_kiekis];
            m.pavarde = pavardes[rand() % pavardziu_kiekis];
            generateRandomGrades(m);

            std::cout << "Sugeneruotas studentas: " << m.vardas << " " << m.pavarde << "\n";
            std::cout << "Sugeneruoti " << m.tarp_rez.size() << " namų darbų rezultatai";
            std::cout << " ir egzamino rezultatas: " << m.egz_rez << "\n";

            students.push_back(m);

            std::string ans;
            std::cout << "Ar norite įvesti dar vieną studentą? (t/n): ";
            std::cin >> ans;
            if (ans != "T" && ans != "t") {
                break;
            }
        }
    }
    else { 
        students = readFromFile("kursiokai.txt");
        if (students.empty()) {
            std::cerr << "Nepavyko nuskaityti jokių duomenų iš failo. Programa baigiama." << std::endl;
            return 1;
        }
        std::cout << "Iš failo nuskaityta " << students.size() << " studentų.\n";
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
