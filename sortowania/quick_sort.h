#ifndef QUICK_SORT_H
#define QUICK_SORT_H

using namespace std;

// Funkcja wybieraj¹ca pivot metod¹ mediany trzech
template <typename T>
void choose_pivot(T* start, T* end)
{
    T* middle = start + (end - start) / 2;

    // Sortujemy trzy elementy
    if (*middle < *start) swap(*middle, *start);
    if (*(end - 1) < *start) swap(*(end - 1), *start);
    if (*(end - 1) < *middle) swap(*(end - 1), *middle);

    // Umieszczamy medianê na koñcu (pivot)
    swap(*middle, *(end - 1));
}

// Funkcja dziel¹ca tablicê wzglêdem pivota
template <typename T>
T* partition(T* start, T* end)
{
    choose_pivot(start, end); // Wybierz pivot metod¹ mediany trzech

    T pivot_value = *(end - 1); // Wartoœæ pivota
    T* i = start; // Indeks mniejszych elementów

    for (T* j = start; j < end - 1; ++j)
    {
        if (*j <= pivot_value)
        {
            swap(*i, *j); // Zamiana miejscami elementów
            ++i;
        }
    }

    swap(*i, *(end - 1)); // Umieszczamy pivot na w³aœciwe miejsce
    return i; // Zwracamy wskaŸnik na pozycjê pivota
}

// Funkcja g³ówna - rozpoczyna sortowanie na podanym zakresie
template <typename T>
void quickSort(T array[], int left, int right)
{
    if (left < right)
    {
        T* start = array + left;
        T* end = array + right + 1; // +1 bo end wskazuje ZA ostatni
        T* pivot = partition(start, end);
        quickSort(array, left, pivot - array - 1);
        quickSort(array, pivot - array + 1, right);
    }
}

#endif // QUICK_SORT_H
