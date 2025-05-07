#include <iostream>
#include <chrono>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <string>
#include <cstring>

#include "quick_sort.h"
#include "merge_sort.h"
#include "intro_sort.h"

using namespace std;
using namespace chrono;

// Funkcja do generowania tablicy losowych liczb
int* generateRandomArray(int size) {
    int* arr = new int[size];
    for (int i = 0; i < size; ++i)
        arr[i] = rand();
    return arr;
}

// Funkcja do częściowego posortowania tablicy
void partiallySort(int* arr, int size, double sortedPercentage) {
    if (sortedPercentage == -1.0) {
        sort(arr, arr + size, greater<int>());
    }
    else {
        int sortedCount = static_cast<int>(size * sortedPercentage);
        sort(arr, arr + sortedCount);
    }
}

// Funkcja do pomiaru czasu sortowania
double measureSortingTime(void (*sorter)(int[], int, int), int* arr, int size) {
    auto startTime = high_resolution_clock::now();
    sorter(arr, 0, size - 1);
    auto endTime = high_resolution_clock::now();
    chrono::duration<double> duration = endTime - startTime;
    return duration.count();
}

// Sprawdza czy plik istnieje i nie jest pusty
bool nonEmptyFileExists(const string& filename) {
    ifstream file(filename, ios::binary | ios::ate);
    return file.is_open() && file.tellg() > 0;
}

// Funkcja do wykonania testów dla danego sortera
void runTests(const string& sorterName, void (*sorter)(int*, int, int)) {
    srand(time(nullptr));

    int sizes[] = { 100, 500, 1000, 5000, 10000, 50000, 100000, 500000, 1000000 };
    double sortedPercentages[] = { -1.0, 0.0, 0.25, 0.5, 0.75, 0.95, 0.99, 0.997 };
    const int numberOfTests = 100;

    ofstream resultFile;
    int fileIndex = 1;
    string baseFilename = sorterName + "_results_";
    string filename;

    while (true) {
        filename = baseFilename + to_string(fileIndex) + ".txt";
        if (!nonEmptyFileExists(filename)) {
            resultFile.open(filename, ios::out);
            break;
        }
        ++fileIndex;
    }

    if (!resultFile.is_open()) {
        cerr << "Nie można otworzyć pliku wynikowego: " << filename << endl;
        return;
    }

    resultFile << "Rozmiar tablicy\tProcent posortowania\tCzas [ms]\n";
    cout << "Zbieranie danych dla: " << sorterName << " (plik: " << filename << ")\n";

    for (int size : sizes) {
        for (double percentage : sortedPercentages) {
            double totalTime = 0.0;

            for (int test = 0; test < numberOfTests; ++test) {
                int* arr = generateRandomArray(size);
                partiallySort(arr, size, percentage);
                totalTime += measureSortingTime(sorter, arr, size);
                delete[] arr;
            }

            double averageTime = totalTime / numberOfTests;

            cout << setw(12) << size
                << setw(22) << fixed << setprecision(3) << (percentage * 100)
                << setw(20) << fixed << setprecision(5) << averageTime
                << endl;

            resultFile << size << "\t" << (percentage * 100) << "\t" << averageTime * 1000 << "\n";
        }
    }

    resultFile.close();
    cout << "Pomiar zakończony dla: " << sorterName << "\n\n";
}

int main() {
    runTests("quicksort", quickSort<int>);
    runTests("mergesort", mergeSort<int>);
    runTests("introsort", introSort<int>);
    return 0;
}
