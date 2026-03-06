#ifndef MOKINYS_H
#define MOKINYS_H

#include <string>

struct Mokinys {
    std::string vardas;
    std::string pavarde;
    int* tarp_rez;
    int tarp_count;
    int egz_rez;
    float galutinis;
};

float calculateAverage(int arr[], int size);
float calculateMedian(int arr[], int size);
void generateRandomGrades(Mokinys& mokinys);
void readStudentData(Mokinys& mokinys);
void calculateFinalGrade(Mokinys& mokinys, const std::string& choice);
void displayResults(Mokinys* students[], int count, const std::string& choice);

#endif
