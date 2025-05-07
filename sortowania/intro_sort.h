#ifndef INTRO_SORT_H
#define INTRO_SORT_H

#include <cmath>       // do log2
#include <algorithm>   // dla swap()
#include "quick_sort.h" // U¿ywamy partition z QuickSort
using namespace std;

// Funkcja naprawiaj¹ca kopiec (heapify) od wêz³a i w dó³
template <typename T>
void heapify(T* array, T* start, int size, int index)
{
    int largest = index; // Zak³adamy, ¿e najwiêkszy jest na pozycji index
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size && *(start + left) > *(start + largest))
        largest = left;

    if (right < size && *(start + right) > *(start + largest))
        largest = right;

    if (largest != index)
    {
        swap(*(start + index), *(start + largest));
        heapify(array, start, size, largest); // Rekurencja na poddrzewie
    }
}

// Funkcja buduj¹ca kopiec (heapify ca³a tablica)
template <typename T>
void buildHeap(T* array, T* start, T* end)
{
    auto n = end - start;
    for (int i = n / 2 - 1; i >= 0; --i)
    {
        heapify(array, start, n, i);
    }
}

// Funkcja wykonuj¹ca sortowanie przez kopcowanie
template <typename T>
void heapSort(T* array, T* start, T* end)
{
    auto size = end - start;
    buildHeap(array, start, end);

    for (int i = size - 1; i > 0; --i)
    {
        swap(*start, *(start + i)); // Zamieñ najwiêkszy element z ostatnim
        heapify(array, start, i, 0); // Napraw kopiec dla zmniejszonego rozmiaru
    }
}


// Rekurencyjna funkcja introspektywna
template <typename T>
void introspectiveSort(T* array, T* start, T* end, int depthLimit)
{
    auto size = end - start;
    if (size <= 1)
        return;

    if (depthLimit == 0)
    {
        heapSort(array, start, end); // Przechodzimy do sortowania przez kopcowanie
        return;
    }

    // U¿ywamy partition z QuickSort
    T* pivot = partition(start, end); // Wywo³anie partition z QuickSort
    introspectiveSort(array, start, pivot, depthLimit - 1);
    introspectiveSort(array, pivot + 1, end, depthLimit - 1);
}



// Funkcja realizuj¹ca sortowanie introspektywne (IntroSort)
// QuickSort + w³asne sortowanie przez kopcowanie
template <typename T>
void introSort(T array[], int left, int right)
{
    if (left < right)
    {
        T* start = array + left;
        T* end = array + right + 1;
        int maxDepth = 2 * log2(end - start);
        introspectiveSort(array, start, end, maxDepth);
    }
}

#endif // INTRO_SORT_H
