#include <iostream>
using namespace std;

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void buildMaxHeap(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

void print(int arr[], int n) {
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

void heapSort(int arr[], int n) {
    buildMaxHeap(arr, n);

    cout << "After building Max Heap: ";
    print(arr, n);

    for (int i = n - 1; i > 0; i--) {

        swap(arr[0], arr[i]);

        cout << "After swap: ";
        print(arr, n);

        heapify(arr, i, 0);
    }
}

int main() {
    int arr[] = {25, 14, 2, 20, 10, 8};
    int n = 6;

    heapSort(arr, n);

    cout << "Final Sorted Array: ";
    print(arr, n);

    return 0;
}