# objektinis_programavimas (v1.0)

Objektinio programavimo repozitorija. Ši versija (v1.0) pritaiko tris skirtingus konteinerius (vector, list, deque) ir tris studentų dalijimo strategijas.

## Sistemos specifikacijos

| Parametras | Reikšmė |
|------------|---------|
| **CPU** | AMD Ryzen 5 5600H with Radeon Graphics |
| **RAM** | 13 GB DDR4 |
| **Diskas** | NVMe SSD 476.9 GB |
| **OS** | Linux |
| **Kompiliatorius** | g++ (C++17) |
| **Optimizacija** | -O3 |

## Paleidimo instrukcijos

```bash
# Kompiliavimas
make

# Paleidimas
make run
# arba
./program

# Valymas
make clean
```

## Konteineriai

Programa palaiko tris C++ STL konteinerių tipus:

| Konteineris | Charakteristika |
|-------------|-----------------|
| **std::vector** | Dinaminis masyvas, greita O(1) prieiga, lėtas įterpimas/trynimas viduryje |
| **std::list** | Dvikryptis sąrašas, lėta O(n) prieiga, greitas įterpimas/trynimas |
| **std::deque** | Dvikryptė eilė, greita prieiga, efektyvus įterpimas abiejose pusėse |

## Strategijos

### 1 strategija: Du nauji konteineriai
Bendro studentų konteinerio skaidymas į du naujus to paties tipo konteinerius: "vargšiukų" ir "kietiakų". Originalus konteineris išlieka nepakitęs.

### 2 strategija: Vienas naujas + trynimas
Bendro studentų konteinerio skaidymas panaudojant tik vieną naują konteinerį: "vargšiukai". Vargšiukai perkeliami į naują konteinerį ir trinami iš originalaus naudojant `erase()`.

**Dėmesio:** Su vector ši strategija yra labai neefektyvi dėl O(n) erase() operacijos!

### 3 strategija: std::stable_partition / splice
Optimizuotas skaidymas naudojant C++ STL algoritmus:
- **vector/deque:** `std::stable_partition`
- **list:** `splice` (efektyviai perkelia elementus be kopijavimo)

## Tyrimų rezultatai

### Strategija 1 (1k, 10k, 100k)

| Konteineris | Įrašai | Nuskaitymas | Rūšiavimas | Dalijimas | Išvedimas | Bendra |
|:------------|:-------|:------------|:-----------|:----------|:----------|:-------|
| vector | 1 000 | 0.0005 s | 0.0001 s | 0.0000 s | 0.0004 s | 0.0010 s |
| list | 1 000 | 0.0004 s | 0.0001 s | 0.0001 s | 0.0005 s | 0.0011 s |
| deque | 1 000 | 0.0004 s | 0.0001 s | 0.0000 s | 0.0004 s | 0.0010 s |
| vector | 10 000 | 0.0053 s | 0.0013 s | 0.0007 s | 0.0037 s | 0.0110 s |
| list | 10 000 | 0.0048 s | 0.0011 s | 0.0006 s | 0.0036 s | 0.0102 s |
| deque | 10 000 | 0.0047 s | 0.0016 s | 0.0002 s | 0.0036 s | 0.0101 s |
| vector | 100 000 | 0.0521 s | 0.0172 s | 0.0108 s | 0.0362 s | 0.1164 s |
| list | 100 000 | 0.0493 s | 0.0233 s | 0.0142 s | 0.0480 s | 0.1348 s |
| deque | 100 000 | 0.0559 s | 0.0215 s | 0.0045 s | 0.0404 s | 0.1222 s |

### Strategija 2 (1k, 10k) - *vector praleistas didesniams failams*

| Konteineris | Įrašai | Nuskaitymas | Rūšiavimas | Dalijimas | Išvedimas | Bendra |
|:------------|:-------|:------------|:-----------|:----------|:----------|:-------|
| vector | 1 000 | 0.0004 s | 0.0001 s | 0.0036 s | 0.0004 s | 0.0045 s |
| list | 1 000 | 0.0004 s | 0.0001 s | 0.0000 s | 0.0003 s | 0.0008 s |
| deque | 1 000 | 0.0004 s | 0.0001 s | 0.0000 s | 0.0003 s | 0.0009 s |
| vector | 10 000 | 0.0044 s | 0.0013 s | 0.3634 s | 0.0025 s | 0.3716 s |
| list | 10 000 | 0.0051 s | 0.0011 s | 0.0002 s | 0.0024 s | 0.0089 s |
| deque | 10 000 | 0.0047 s | 0.0015 s | 0.0002 s | 0.0026 s | 0.0090 s |

### Strategija 3 (1k, 10k, 100k)

| Konteineris | Įrašai | Nuskaitymas | Rūšiavimas | Dalijimas | Išvedimas | Bendra |
|:------------|:-------|:------------|:-----------|:----------|:----------|:-------|
| vector | 1 000 | 0.0004 s | 0.0001 s | 0.0001 s | 0.0003 s | 0.0010 s |
| list | 1 000 | 0.0004 s | 0.0001 s | 0.0000 s | 0.0005 s | 0.0010 s |
| deque | 1 000 | 0.0004 s | 0.0001 s | 0.0000 s | 0.0003 s | 0.0009 s |
| vector | 10 000 | 0.0050 s | 0.0013 s | 0.0004 s | 0.0025 s | 0.0091 s |
| list | 10 000 | 0.0051 s | 0.0011 s | 0.0001 s | 0.0025 s | 0.0089 s |
| deque | 10 000 | 0.0043 s | 0.0015 s | 0.0004 s | 0.0026 s | 0.0088 s |
| vector | 100 000 | 0.0494 s | 0.0171 s | 0.0159 s | 0.0244 s | 0.1068 s |
| list | 100 000 | 0.0419 s | 0.0248 s | 0.0087 s | 0.0347 s | 0.1100 s |
| deque | 100 000 | 0.0560 s | 0.0212 s | 0.0130 s | 0.0283 s | 0.1185 s |

## Išvados

### Geriausia strategija

| Konteineris | Rekomenduojama strategija | Kodėl |
|-------------|--------------------------|-------|
| **vector** | 3 (stable_partition) | Greičiausia, efektyvi atmintis |
| **list** | 3 (splice) | Greičiausia, nereikia kopijuoti |
| **deque** | 2 arba 3 | Abi veikia panašiai greitai |

### Kodėl strategija 2 su vector yra bloga?

Vector: kiekvienas erase() reikalauja perkelti visus elementus į dešinę. Su 10 000 įrašų: dalijimas užtruko 0.36 s (vietoj 0.0004 s su list). Su 100 000 įrašų: būtų užtrukę ~36 sekundes!

### Rekomendacija

**Naudokite Vector su Strategija 3** - tai greičiausia ir atminties efektyvi pasirinkimo strategija.

## Failų struktūra

```
.
├── main.cpp           # Pagrindinė programa su tyrimais
├── benchmark.h        # Benchmark struktūros ir deklaracijos
├── benchmark.cpp      # Benchmark implementacija
├── student.h          # Mokinys struktūra ir šabloninės funkcijos
├── Makefile           # Kompiliavimo instrukcija
├── README.md          # Šis dokumentas
└── rezultatai.csv     # Tyrimų rezultatai (sugeneruojami)
```

## Rezultatų failo formatas

Rezultatai išsaugomi CSV faile `rezultatai.csv`:

```
Konteineris,Strategija,Irasu_kiekis,Nuskaitymas_s,Rusiavimas_s,Dalijimas_s,Isvedimas_s,Bendra_s
vector,1,1000,0.0005,0.0001,0.0000,0.0004,0.0010
```
