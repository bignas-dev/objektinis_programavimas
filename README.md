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
Bendro studentų konteinerio skaidymas panaudojant tik vieną naują konteinerį: "vargšiukai". Vargšiukai perkeliami į naują konteinerį ir ištrinami iš originalaus.

#### 3 strategija
Optimizuotas skaidymas naudojant `std::stable_partition` (vector/deque) arba `splice` (list).

### Tyrimų rezultatai

Rezultatai išsaugomi faile `rezultatai.csv` po kiekvieno programos paleidimo.

## Spartos analizė (v0.4)

Tyrimas atliktas naudojant `std::vector` konteinerį ir `-O3` optimizaciją.

| Įrašų kiekis | Failo kūrimas | Nuskaitymas | Rūšiavimas | Išvedimas | Bendra |
| :--- | :--- | :--- | :--- | :--- | :--- |
| 1 000 | 0.0004 s | 0.0005 s | 0.0001 s | 0.0003 s | 0.0009 s |
| 10 000 | 0.0038 s | 0.0069 s | 0.0015 s | 0.0023 s | 0.0107 s |
| 100 000 | 0.0370 s | 0.0571 s | 0.0132 s | 0.0221 s | 0.0925 s |
| 1 000 000 | 0.3664 s | 0.5513 s | 0.1400 s | 0.2373 s | 0.9286 s |
| 10 000 000 | 3.8306 s | 6.4140 s | 2.1147 s | 2.4790 s | 11.0077 s |

### Sistemos specifikacijos
*   **Platforma:** Linux
*   **Optimizacija:** -O3

### Tyrimo išvados (v0.4)
1.  **Nuskaitymas:** Tai pati lėčiausia operacija dėl I/O operacijų ir `std::istringstream` naudojimo.
2.  **Rūšiavimas:** Skirstymas į dvi grupes naudojant `push_back` yra pakankamai greitas.
3.  **Generatorius:** Failų generavimas vyksta efektyviai, tačiau rašymas į diską išlieka butelio kakleliu.
