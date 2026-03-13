# objektinis_programavimas (v0.4)

Objektinio programavimo repozitorija. Šioje versijoje (v0.4) pridėtas failų generatorius ir atliktas programos spartos tyrimas.

## Paleidimo instrukcijos

1. Klonuokite git repozitorją.
2. Kompiliuokite programą naudojant `g++ -O3 -o program main.cpp student.cpp generator.cpp utils.cpp`.
3. Paleiskite `./program`.

## Spartos analizė (v0.4)

Tyrimas atliktas naudojant `std::vector` konteinerį ir `-O3` optimizaciją. Išmatuotas laikas (sekundėmis) skirtingoms operacijoms su penkiais failų dydžiais.

| Įrašų kiekis | Failo kūrimas (1 tyrimas) | Nuskaitymas | Rūšiavimas į kategorijas | Išvedimas į 2 failus | Bendra programa (2 tyrimas) |
| :--- | :--- | :--- | :--- | :--- | :--- |
| 1 000 | 0.0004 s | 0.0005 s | 0.0001 s | 0.0003 s | 0.0009 s |
| 10 000 | 0.0038 s | 0.0069 s | 0.0015 s | 0.0023 s | 0.0107 s |
| 100 000 | 0.0370 s | 0.0571 s | 0.0132 s | 0.0221 s | 0.0925 s |
| 1 000 000 | 0.3664 s | 0.5513 s | 0.1400 s | 0.2373 s | 0.9286 s |
| 10 000 000 | 3.8306 s | 6.4140 s | 2.1147 s | 2.4790 s | 11.0077 s |

### Sistemos specifikacijos
*   **Platforma:** Linux
*   **Optimizacija:** -O3

### Tyrimo išvados
1.  **Nuskaitymas:** Tai pati lėčiausia operacija dėl I/O operacijų ir `std::istringstream` naudojimo.
2.  **Rūšiavimas:** Skirstymas į dvi grupes naudojant `push_back` yra pakankamai greitas, tačiau prie 10M įrašų užtruko apie 2 sekundes.
3.  **Generatorius:** Failų generavimas vyksta efektyviai, tačiau rašymas į diską išlieka butelio kakleliu.
