#include <iostream>
using namespace std;

class MaxHeap {
    int arr[1000];
    int size;

public:
    MaxHeap() {
        size = 0;
    }

    void insert(int value) {
        size++;
        int i = size;
        arr[i] = value;

        while (i > 1) {
            int parent = i / 2;

            if (arr[parent] < arr[i]) {
                swap(arr[parent], arr[i]);
                i = parent;
            } else {
                break;
            }
        }
    }

    int extractMax() {
        if (size == 0)
            return -1;

        int maxVal = arr[1];
        arr[1] = arr[size];
        size--;

        int i = 1;

        while (true) {
            int left = 2 * i;
            int right = 2 * i + 1;
            int largest = i;

            if (left <= size && arr[left] > arr[largest])
                largest = left;

            if (right <= size && arr[right] > arr[largest])
                largest = right;

            if (largest != i) {
                swap(arr[i], arr[largest]);
                i = largest;
            } else {
                break;
            }
        }

        return maxVal;
    }
};

int main() {
    MaxHeap h;

    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        h.insert(x);
    }

    cout << "Top 3 largest elements: ";

    int limit = (n < 3) ? n : 3;

    for (int i = 0; i < limit; i++) {
        cout << h.extractMax() << " ";
    }

    cout << endl;

    return 0;
}