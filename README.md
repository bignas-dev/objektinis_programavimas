# objektinis_programavimas (v1.0)

Objektinio programavimo repozitorija. Ši versija (v1.0) pritaiko tris skirtingus konteinerius (vector, list, deque) ir tris studentų dalijimo strategijas.

## Paleidimo instrukcijos

1. Klonuokite git repozitoriją.
2. Kompiliuokite programą naudojant `make` arba `g++ -O3 -std=c++17 -o program main.cpp benchmark.cpp`.
3. Paleiskite `./program` arba `make run`.
4. Rezultatai bus išsaugoti faile `rezultatai.csv`.

## Diegimo instrukcijos (Unix)

```bash
git clone <repo_url>
cd objektinis_programavimas
make
./program
```

## v1.0 Tyrimai

### Konteineriai
Programa palaiko tris konteinerių tipus:
- `std::vector<Mokinys>`
- `std::list<Mokinys>`
- `std::deque<Mokinys>`

### Strategijos

#### 1 strategija
Bendro studentų konteinerio skaidymas į du naujus to paties tipo konteinerius: "vargšiukų" ir "kietiakų". Originalus konteineris išlieka nepakitęs.

#### 2 strategija
Bendro studentų konteinerio skaidymas panaudojant tik vieną naują konteinerį: "vargšiukai". Vargšiukai perkeliami į naują konteinerį ir ištrinami iš originalaus naudojant `erase()`.

#### 3 strategija
Optimizuotas skaidymas naudojant `std::stable_partition` (vector/deque) arba `splice` (list).

### Sistemos specifikacijos
*   **Platforma:** Linux
*   **Kompiliatorius:** g++ su -O3 optimizacija
*   **Standartas:** C++17

### Tyrimų rezultatai (100000 įrašų)

| Konteineris | Strategija | Nuskaitymas | Rūšiavimas | Dalijimas | Bendra |
|:---|:---|:---|:---|:---|:---|
| vector | 1 | 0.0521 s | 0.0172 s | 0.0108 s | 0.1164 s |
| vector | 2 | 0.0407 s | 0.0173 s | 36.41 s | 36.49 s |
| vector | 3 | 0.0494 s | 0.0171 s | 0.0159 s | 0.1068 s |
| list | 1 | 0.0493 s | 0.0233 s | 0.0142 s | 0.1348 s |
| list | 2 | 0.0489 s | 0.0224 s | 0.0118 s | 0.1184 s |
| list | 3 | 0.0419 s | 0.0248 s | 0.0087 s | 0.1100 s |
| deque | 1 | 0.0559 s | 0.0215 s | 0.0045 s | 0.1222 s |
| deque | 2 | 0.0567 s | 0.0211 s | 0.0049 s | 0.1079 s |
| deque | 3 | 0.0560 s | 0.0212 s | 0.0130 s | 0.1185 s |

### Išvados

1. **Strategija 2 su vector:** Labai neefektyvi dėl O(n) `erase()` operacijos. Su 100k įrašų užtruko 36 sekundes, o su kitais konteineriais - mažiau nei 0.02 s.

2. **Geriausia strategija:** 
   - Vector: 3 strategija (std::stable_partition)
   - List: 3 strategija (splice) 
   - Deque: 2 arba 3 strategija

3. **Konteinerių palyginimas:**
   - Vector su 1 ir 3 strategija veikia greičiausiai
   - List turi lėčiausią rūšiavimą (nenaudoja atsitiktinės prieigos)
   - Deque užima tarpinę vietą, stabilus su visomis strategijomis

4. **Rekomendacija:** Naudoti vector su 3 strategija efektyviausiems rezultatams pasiekti.

## Spartos analizė (v0.4)

Tyrimas atliktas naudojant `std::vector` konteinerį ir `-O3` optimizaciją.

| Įrašų kiekis | Failo kūrimas | Nuskaitymas | Rūšiavimas | Išvedimas | Bendra |
| :--- | :--- | :--- | :--- | :--- | :--- |
| 1 000 | 0.0004 s | 0.0005 s | 0.0001 s | 0.0003 s | 0.0009 s |
| 10 000 | 0.0038 s | 0.0069 s | 0.0015 s | 0.0023 s | 0.0107 s |
| 100 000 | 0.0370 s | 0.0571 s | 0.0132 s | 0.0221 s | 0.0925 s |
| 1 000 000 | 0.3664 s | 0.5513 s | 0.1400 s | 0.2373 s | 0.9286 s |

## Failų struktūra

```
├── main.cpp           # Pagrindinė programa
├── benchmark.h/cpp    # Spartos tyrimų modulis
├── student.h          # Mokinys struktūra ir šablonai
├── Makefile           # Kompiliavimo instrukcija
└── README.md          # Dokumentacija
```
