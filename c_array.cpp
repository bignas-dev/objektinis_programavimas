#include <iomanip>
#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>

struct Mokinys {
    std::string vardas;
    std::string pavarde;
    int* tarp_rez;
    int tarp_count;
    int egz_rez;
    float galutinis;
};

float calculateAverage(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += arr[i];
    }
    return static_cast<float>(sum) / static_cast<float>(size);
}

float calculateMedian(int arr[], int size) {
    int* temp = new int[size];
    for (int i = 0; i < size; ++i){
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

    if (count == 0) {
        std::cout << "Turite įvesti bent vieną tarpinį rezultatą.\n";
        exit(1);
    }

    int* final_grades = new int[count];
    for (int i = 0; i < count; ++i) {
        final_grades[i] = grades[i];
    }
    delete[] grades;
    mokinys.tarp_rez = final_grades;
    mokinys.tarp_count = count;

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
        tarp_rez = calculateAverage(mokinys.tarp_rez, mokinys.tarp_count);
    } else {
        tarp_rez = calculateMedian(mokinys.tarp_rez, mokinys.tarp_count);
    }
    mokinys.galutinis = 0.6 * mokinys.egz_rez + 0.4 * tarp_rez;
}

void displayResults(Mokinys* students[], int count, std::string choice) {
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

    int student_capacity = 2;
    int student_count = 0;
    Mokinys** students = new Mokinys*[student_capacity];

    while (true) {
        std::cout << "\nĮveskite " << student_count + 1 << " studento duomenis:\n";
        Mokinys* m = new Mokinys;

        if (input_mode == 1) {
            readStudentData(*m);
        } else {
            std::cout << "Įveskite vardą: ";
            std::cin >> m->vardas;
            std::cout << "Įveskite pavardę: ";
            std::cin >> m->pavarde;
            generateRandomGrades(*m);
            std::cout << "Sugeneruoti " << m->tarp_count << " namų darbų rezultatai";
            std::cout << " ir egzamino rezultatas: " << m->egz_rez << "\n";
        }

        if (student_count == student_capacity) {
            student_capacity *= 2;
            Mokinys** new_students = new Mokinys*[student_capacity];
            for (int i = 0; i < student_count; ++i)
                new_students[i] = students[i];
            delete[] students;
            students = new_students;
        }
        students[student_count++] = m;

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

    for (int i = 0; i < student_count; ++i) {
        calculateFinalGrade(*students[i], choice);
    }

    displayResults(students, student_count, choice);

    for (int i = 0; i < student_count; ++i) {
        delete[] students[i]->tarp_rez;
        delete students[i];
    }
    delete[] students;

    return 0;
}
