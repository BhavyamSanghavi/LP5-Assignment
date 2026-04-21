#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

int main() {
    int arr[] = {5, 2, 9, 1, 7, 3};
    int n = 6;

    int sum = 0;
    int min_val = arr[0];
    int max_val = arr[0];

    #pragma omp parallel for reduction(+:sum) reduction(min:min_val) reduction(max:max_val)
    for (int i = 0; i < n; i++) {
        sum += arr[i];

        if (arr[i] < min_val)
            min_val = arr[i];

        if (arr[i] > max_val)
            max_val = arr[i];
    }

    float avg = (float)sum / n;

    cout << "Sum: " << sum << endl;
    cout << "Min: " << min_val << endl;
    cout << "Max: " << max_val << endl;
    cout << "Average: " << avg << endl;

    return 0;
}