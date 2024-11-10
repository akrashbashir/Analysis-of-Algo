#include <iostream>
using namespace std;

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* left_half = new int[n1];
    int* right_half = new int[n2];

    for (int i = 0; i < n1; i++)
        left_half[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        right_half[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (left_half[i] <= right_half[j]) {
            arr[k++] = left_half[i++];
        } else {
            arr[k++] = right_half[j++];
        }
    }

    while (i < n1)
        arr[k++] = left_half[i++];
    while (j < n2)
        arr[k++] = right_half[j++];

    delete[] left_half;
    delete[] right_half;
}

void mergesort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergesort(arr, left, mid);
        mergesort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int partition(int arr[], int left, int right) {
    int pivot = arr[right];
    int i = left - 1;

    for (int j = left; j < right; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[right]);
    return i + 1;
}

void hybridSort(int arr[], int left, int right, int threshold) {
    if (right - left <= threshold) {
        mergesort(arr, left, right);  // Switch to MergeSort when below threshold
    } else if (left < right) {
        int pivot = partition(arr, left, right);
        hybridSort(arr, left, pivot - 1, threshold);
        hybridSort(arr, pivot + 1, right, threshold);
    }
}

int main() {
    int arr[] = {64, 25, 12, 22, 11, 35, 80, 90, 45};
    int n = sizeof(arr) / sizeof(arr[0]);
    int threshold = 10;

    hybridSort(arr, 0, n - 1, threshold);

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;

    return 0;
}
