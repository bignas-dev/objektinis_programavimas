#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>

struct Mokinys {
    std::string vardas;
    std::string pavarde;
    std::vector<int> tarp_rez;
    int egz_rez;
    float galutinis;
};

float calculateAverage(const std::vector<int>& arr);
float calculateMedian(std::vector<int> arr);
void generateRandomGrades(Mokinys& mokinys);
void readStudentData(Mokinys& mokinys);
std::vector<Mokinys> readFromFile(const std::string& filename);
void calculateFinalGrade(Mokinys& mokinys, const std::string& choice);
void displayResults(const std::vector<Mokinys>& students, const std::string& choice);

#endif
