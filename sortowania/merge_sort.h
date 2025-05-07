#ifndef MERGE_SORT_H
#define MERGE_SORT_H

// Funkcja pomocnicza: scala dwie posortowane czêœci
template <typename T>
void merge(T* arr, int left, int mid, int right, T* mergeBuffer) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j])
            mergeBuffer[k++] = arr[i++];
        else
            mergeBuffer[k++] = arr[j++];
    }

    while (i <= mid)
        mergeBuffer[k++] = arr[i++];
    while (j <= right)
        mergeBuffer[k++] = arr[j++];

    for (int l = left; l <= right; ++l)
        arr[l] = mergeBuffer[l];
}

// Rekurencyjna czêœæ MergeSort
template <typename T>
void mergeSortRecursive(T* arr, int left, int right, T* mergeBuffer) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    mergeSortRecursive(arr, left, mid, mergeBuffer);
    mergeSortRecursive(arr, mid + 1, right, mergeBuffer);
    merge(arr, left, mid, right, mergeBuffer);
}

// G³ówna funkcja sortuj¹ca z zakresem
template <typename T>
void mergeSort(T* arr, int left, int right) {
    if (left >= right)
        return;

    T* mergeBuffer = new T[right + 1];
    mergeSortRecursive(arr, left, right, mergeBuffer);
    delete[] mergeBuffer;
}

#endif // MERGE_SORT_H
