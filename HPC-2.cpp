#include<bits/stdc++.h>
#include<omp.h>
using namespace std;

// ---------- BUBBLE SORT ----------

// Sequential Bubble Sort
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1])
                swap(arr[j], arr[j+1]);
        }
    }
}

// Parallel Bubble Sort
void parallelBubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n; i++) {
        #pragma omp parallel for
        for (int j = (i % 2); j < n-1; j += 2) {
            if (arr[j] > arr[j+1])
                swap(arr[j], arr[j+1]);
        }
    }
}

// ---------- MERGE SORT ----------

void merge(vector<int>& arr, int l, int m, int r) {
    vector<int> temp(r - l + 1);
    int i = l, j = m+1, k = 0;

    while (i <= m && j <= r) {
        if (arr[i] < arr[j]) temp[k++] = arr[i++];
        else temp[k++] = arr[j++];
    }

    while (i <= m) temp[k++] = arr[i++];
    while (j <= r) temp[k++] = arr[j++];

    for (int i = 0; i < k; i++)
        arr[l + i] = temp[i];
}

// Sequential Merge Sort
void mergeSort(vector<int>& arr, int l, int r) {
    if (l >= r) return;
    int m = (l + r) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m+1, r);
    merge(arr, l, m, r);
}

// Parallel Merge Sort
void parallelMergeSort(vector<int>& arr, int l, int r) {
    if (l >= r) return;

    int m = (l + r) / 2;

    #pragma omp parallel sections
    {
        #pragma omp section
        parallelMergeSort(arr, l, m);

        #pragma omp section
        parallelMergeSort(arr, m+1, r);
    }

    merge(arr, l, m, r);
}

// ---------- MAIN ----------

int main() {
    vector<int> arr = {9, 5, 2, 7, 1, 3, 8, 6, 4};
    vector<int> arr1 = arr, arr2 = arr, arr3 = arr, arr4 = arr;

    double start, end;

    // Sequential Bubble
    start = omp_get_wtime();
    bubbleSort(arr1);
    end = omp_get_wtime();
    cout << "Sequential Bubble Sort Time: " << end - start << endl;

    // Parallel Bubble
    start = omp_get_wtime();
    parallelBubbleSort(arr2);
    end = omp_get_wtime();
    cout << "Parallel Bubble Sort Time: " << end - start << endl;

    // Sequential Merge
    start = omp_get_wtime();
    mergeSort(arr3, 0, arr3.size()-1);
    end = omp_get_wtime();
    cout << "Sequential Merge Sort Time: " << end - start << endl;

    // Parallel Merge
    start = omp_get_wtime();
    parallelMergeSort(arr4, 0, arr4.size()-1);
    end = omp_get_wtime();
    cout << "Parallel Merge Sort Time: " << end - start << endl;

    return 0;
}