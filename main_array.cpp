#include "mokinys.h"
#include "utils.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdexcept>

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    int input_mode;
    std::cout << "Pasirinkite įvesties būdą:\n"
              << "1 - Rankinis įvedimas\n"
              << "2 - Atsitiktinis generavimas\n"
              << "Jūsų pasirinkimas: ";
    std::cin >> input_mode;

    try {
        if (std::cin.fail() || (input_mode != 1 && input_mode != 2)) {
            throw std::runtime_error("Neteisinga įvestis: tinka '1' arba '2'.\n");
        }
    } catch (const std::runtime_error& e) {
        std::cout << e.what();
        throw;
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
            m->vardas = vardai[rand() % getVarduKiekis()];
            m->pavarde = pavardes[rand() % getPavardziuKiekis()];
            generateRandomGrades(*m);
            
            std::cout << "Sugeneruotas studentas: " << m->vardas << " " << m->pavarde << "\n";
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

    try {
        if (choice != "1" && choice != "2") {
            throw std::runtime_error("Neteisinga įvestis: tinka '1' arba '2'.\n");
        }
    } catch (const std::runtime_error& e) {
        std::cout << e.what();
        throw;
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
