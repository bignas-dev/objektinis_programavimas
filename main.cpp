#include <iomanip>
#include <stdio.h>
#include <iostream>
#include <string>
#include <iomanip>

struct Mokinys{
    std :: string vardas;
    std :: string pavarde;
    int tarp_rez[3];
    int egz_rez;
    float galutinis;
};

int main() {
    Mokinys mokinys1 = Mokinys();
    Mokinys mokinys2 = Mokinys();
    
    printf("Iveskite vardą\n");
    std :: cin >> mokinys1.vardas;
    printf("Iveskite pavardę\n");
    std :: cin >> mokinys1.pavarde;

    for (size_t i = 0; i < 3; ++i) {
        std ::cout << "Įveskite " << i + 1 << " tarpinį rezultatą\n";
        std :: cin >> mokinys1.tarp_rez[i];
    }
    printf("Iveskite egzamino rezulatą\n");
    std :: cin >> mokinys1.egz_rez;

    mokinys1.galutinis = 0.6 * mokinys1.egz_rez;
    for (size_t i = 0; i < 3; ++i) {
        mokinys1.galutinis += 0.4 / 3 * mokinys1.tarp_rez[i];
    }

    printf("Iveskite vardą\n");
    std :: cin >> mokinys2.vardas;
    printf("Iveskite pavardę\n");
    std :: cin >> mokinys2.pavarde;

    for (size_t i = 0; i < 3; ++i) {
        std ::cout << "Įveskite " << i + 1 << " tarpinį rezultatą\n";
        std :: cin >> mokinys2.tarp_rez[i];
    }
    printf("Iveskite egzamino rezulatą\n");
    std :: cin >> mokinys2.egz_rez;

    mokinys2.galutinis = 0.6 * mokinys2.egz_rez;
    for (size_t i = 0; i < 3; ++i) {
        mokinys2.galutinis += 0.4 / 3 * mokinys2.tarp_rez[i];
    }
    std :: cout << mokinys1.galutinis << " " << mokinys2.galutinis << "\n";

    int langelio_ilgis = 20;
    std :: cout << std :: setw(langelio_ilgis) << "Pavardė";
    std :: cout << std :: setw(langelio_ilgis) << "Vardas";
    std :: cout << std :: setw(langelio_ilgis) << "Galutinis (Vid.)";
    std :: cout << "\n";

    std :: cout << std :: setfill('-') << std :: setw(langelio_ilgis * 3) << "";
    std :: cout << std :: setfill(' ') << "\n";

    std :: cout << std :: setw(langelio_ilgis) << mokinys1.pavarde;
    std :: cout << std :: setw(langelio_ilgis) << mokinys1.vardas;
    std :: cout << std :: setw(langelio_ilgis) << std :: setprecision(2) << mokinys1.galutinis;
    std :: cout << "\n";

    std :: cout << std :: setw(langelio_ilgis) << mokinys2.pavarde;
    std :: cout << std :: setw(langelio_ilgis) << mokinys2.vardas;
    std :: cout << std :: setw(langelio_ilgis) << std :: setprecision(2) << mokinys2.galutinis;
    std :: cout << "\n";

    return 0;
}
