# Studentų Valdymo Sistema - v1.0

## Apie Projektą

Ši programa skirta studentų duomenų apdorojimui, rūšiavimui ir skirstymui į dvi kategorijas: "vargšiukus" (galutinis balas < 5.0) ir "kietiakus" (galutinis balas >= 5.0). Programa realizuota naudojant tris skirtingus STL konteinerius (`std::vector`, `std::list`, `std::deque`) ir atliktas išsamus jų veikimo spartos tyrimas.

## Sistemos Reikalavimai

- **Kompiliatorius:** g++ (C++11 arba naujesnis)
- **Operacinė sistema:** Linux/Unix (testuota NixOS)
- **Build sistema:** Make

## Testavimo Sistemos Parametrai

| Komponentas | Specifikacija |
|-------------|---------------|
| **CPU** | AMD Ryzen 5 5600H with Radeon Graphics (6 branduoliai) |
| **RAM** | 14 GB (testavimo metu laisva ~7 GB) |
| **HDD** | SSD |
| **OS** | NixOS 6.18.21 |

## Diegimo Instrukcija

### 1. Projekto parsisiuntimas

```bash
git clone <repo-url>
cd objektinis_programavimas
```

### 2. Kompiliavimas

Naudojant Make:

```bash
# Sukompiliuoti pagrindinę programą
make main

# Sukompiliuoti benchmark programą
make bench

# Sukompiliuoti duomenų generatorių
make gen

# Išvalyti sukompiliuotus failus
make clean
```

## Naudojimo Instrukcija

### Pagrindinė Programa

Paleidus `./main`, programa pasiūlys tris įvesties būdus:

1. **Rankinis įvedimas** - studentų duomenys įvedami per terminalą
2. **Atsitiktinis generavimas** - sugeneruojamas nurodytas kiekis studentų
3. **Nuskaitymas iš failo** - duomenys skaitomi iš paruošto failo

Toliau pasirenkamas galutinio balo skaičiavimo būdas:
- **1** - Vidurkis
- **2** - Mediana

Galiausiai pasirenkamas rūšiavimo kriterijus:
- **1** - Pagal vardą
- **2** - Pagal pavardę
- **3** - Pagal galutinį balą

Ir rezultatų pateikimo būdas:
- **1** - Į terminalą
- **2** - Į failą (`output.txt`)

### Benchmark Programa

Benchmark programa (`./benchmark`) atlieka konteinerių veikimo spartos tyrimą su trimis skirtingomis strategijomis:

```bash
make bench
```

### Duomenų Generatorius

Generatorius sukuria testinius failus su 1k, 10k, 100k, 1M ir 10M įrašų:

```bash
make gen
```

## Konteinerių Tyrimas

### Tyrimo Metodika

Tyrimo metu buvo matuojamas trijų STL konteinerių veikimo spartas atliekant šiuos veiksmus:
1. **Duomenų nuskaitymas** iš failų į konteinerį
2. **Studentų rūšiavimas** didėjimo tvarką
3. **Skirstymas į dvi grupes** (vargšiukai ir kietiakiai)

Testai atlikti su failais: 1k, 10k, 100k, 1M, 10M įrašų.

### Strategijos

#### 1 Strategija - Kopijavimas į du konteinerius
```cpp
for (const auto& s : students) {
    if (s.galutinis < 5.0f) vargsiukai.push_back(s);
    else kietiakiai.push_back(s);
}
```
- Paprasčiausia realizacija
- Sunaudoja daugiausiai atminties (studentai lieka visuose trijuose konteineriuose)
- Greita, nes nėra trynimų operacijų

#### 2 Strategija - Trynimas iš originalaus konteinerio
```cpp
for (auto it = students.begin(); it != students.end(); ) {
    if (it->galutinis < 5.0f) {
        vargsiukai.push_back(std::move(*it));
        it = students.erase(it);
    } else {
        ++it;
    }
}
```
- Efektyvesnė atminties atžvilgiu
- Labai lėta `vector` konteineriui dėl O(n) trynimo operacijos
- Geresnė `list` konteineriui dėl O(1) trynimo

#### 3 Strategija - STL stable_partition algoritmas
```cpp
auto partition_it = std::stable_partition(students.begin(), students.end(),
    [](const Mokinys& s) { return s.galutinis >= 5.0f; });
kietiakiai.assign(students.begin(), partition_it);
vargsiukai.assign(partition_it, students.end());
```
- **Greičiausia strategija visiems konteineriams**
- Naudoja optimizuotą STL algoritmą
- Rekomenduojama naudoti produkcijoje

## Tyrimų Rezultatai

### 1 lentelė. Duomenų generavimo laikas

| Dydis | 1k | 10k | 100k | 1M | 10M |
|-------|-----|------|-------|-------|--------|
| Laikas (ms) | 2 | 18 | 198 | 1752 | 15715 |

### 2 lentelė. Bendras veikimo laikas pagal konteinerius (ms)

| Konteineris | 1k | 10k | 100k | 1M | 10M |
|-------------|-----|------|-------|-------|--------|
| **vector** | 164 | 32 | 307 | 2991 | 23747 |
| **list** | 373 | 26 | 242 | 2044 | 23283 |
| **deque** | 444 | 33 | 307 | 2520 | 23049 |

### 3 lentelė. Vector konteinerio detalūs laikai (ms)

| Dydis | Nuskaitymas | Rūšiavimas | Rašymas | Viso |
|-------|-------------|------------|---------|------|
| 1k | 159 | 0 | 5 | 164 |
| 10k | 20 | 7 | 4 | 32 |
| 100k | 194 | 68 | 44 | 307 |
| 1M | 1874 | 635 | 480 | 2991 |
| 10M | 14677 | 5834 | 3235 | 23747 |

### 4 lentelė. List konteinerio detalūs laikai (ms)

| Dydis | Nuskaitymas | Rūšiavimas | Rašymas | Viso |
|-------|-------------|------------|---------|------|
| 1k | 287 | 0 | 85 | 373 |
| 10k | 16 | 6 | 3 | 26 |
| 100k | 153 | 54 | 34 | 242 |
| 1M | 1308 | 421 | 313 | 2044 |
| 10M | 13992 | 5828 | 3463 | 23283 |

### 5 lentelė. Deque konteinerio detalūs laikai (ms)

| Dydis | Nuskaitymas | Rūšiavimas | Rašymas | Viso |
|-------|-------------|------------|---------|------|
| 1k | 341 | 0 | 102 | 444 |
| 10k | 20 | 7 | 4 | 33 |
| 100k | 194 | 68 | 44 | 307 |
| 1M | 1750 | 442 | 327 | 2520 |
| 10M | 13993 | 5842 | 3214 | 23049 |

### 6 lentelė. Strategijų palyginimas - skirstymo laikas (ms)

| Konteineris | Strategija | 1k | 10k |
|-------------|------------|-----|------|
| **vector** | S1 (copy) | 0 | 7 |
| **vector** | S2 (erase) | 75 | 7678 |
| **vector** | S3 (partition) | 0 | 8 |
| **list** | S1 (copy) | 0 | 3 |
| **list** | S2 (erase) | 0 | 2 |
| **list** | S3 (partition) | 1 | 10 |
| **deque** | S1 (copy) | 0 | 2 |
| **deque** | S2 (erase) | 25 | 2325 |
| **deque** | S3 (partition) | 0 | 5 |

### Išvados

1. **std::vector** yra greičiausias konteineris mažiems dydžiams dėl:
   - Gerų cache charakteristikų (tęstinė atmintis)
   - Optimizuoto push_back veikimo
   - Greito random access

2. **std::list** pasirodė esanti greitesnė dideliems dydžiams (1M, 10M) dėl:
   - O(1) insert/delete operacijų
   - Nėra atminties perskirstymo kaip vector atveju

3. **std::deque** užima tarpinę poziciją tarp vector ir list

4. **3 strategija (stable_partition)** yra greičiausia vector ir deque konteineriams:
   - Naudoja optimizuotą STL algoritmą
   - Sumažina operacijų skaičių

5. **2 strategija (erase)** yra prasčiausia vector ir deque konteineriams:
   - Vector: 7678ms (10k įrašų) - O(n) trynimas kiekvienam elementui
   - Deque: 2325ms (10k įrašų) - panašus efektas
   - List: 2ms (10k įrašų) - O(1) trynimas, todėl labai greita

6. **List konteineriui 2 strategija yra optimaliausia** dėl O(1) erase operacijos

7. **Vector konteineriui 1 ir 3 strategijos yra optimaliausios** - beveik identiškas greitis

## Projekto Struktūra

```
objektinis_programavimas/
├── main.cpp           # Pagrindinė programa
├── student.h          # Studento struktūra ir pagalbinės funkcijos
├── benchmark.cpp      # Konteinerių spartos testavimas
├── generator.cpp      # Testinių duomenų generatorius
├── Makefile           # Build sistema
├── README.md          # Šis failas
└── .gitignore         # Git ignore failas
```

## Versijų Istorija

### v1.0 (Finalinė versija)
- Pilnai realizuoti trys konteineriai: vector, list, deque
- Implementuotos trys skirstymo strategijos
- Atliktas išsamus konteinerių palyginimo tyrimas
- Parengta Makefile build sistema
- Pilna dokumentacija README.md faile

### v0.4
- Bazinė programos versija su vector konteineriu
- Studentų duomenų nuskaitymas iš failų
- Rūšiavimas ir skirstymas į dvi grupes

### v0.1 - v0.3
- Pagrindinio funkcionalumo kūrimas
- Duomenų struktūrų projektavimas
- Failų skaitymo/rašymo implementacija

## Paleidimo Pavyzdžiai

### 1. Pagrindinės programos paleidimas
```bash
make main
# arba
./main
```

### 2. Benchmark paleidimas
```bash
make bench
# arba
./benchmark
```

### 3. Duomenų generavimas
```bash
make gen
# arba
./generator
```

## Autoriai

- Sukurta kaip objektinio programavimo kurso projektas

## Licencija

Šis projektas sukurtas edukaciniais tikslais.
