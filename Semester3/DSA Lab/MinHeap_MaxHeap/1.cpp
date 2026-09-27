#include <iostream>
using namespace std;

class MaxHeap {
    int arr[100];
    int size;

public:
    MaxHeap() {
        size = 0;
    }

    void insert(int value) {
        size++;
        int index = size;
        arr[index] = value;

        while (index > 1) {
            int parent = index / 2;

            if (arr[parent] < arr[index]) {
                swap(arr[parent], arr[index]);
                index = parent;
            } else {
                break;
            }
        }
    }

    void deleteRoot() {
        if (size == 0)
            return;

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
    }

    void print() {
        for (int i = 1; i <= size; i++)
            cout << arr[i] << " ";
        cout << endl;
    }
};

int main() {
    MaxHeap h;

    h.insert(55);
    h.insert(54);
    h.insert(53);
    h.insert(50);
    h.insert(52);

    cout << "Before deletion: ";
    h.print();

    h.deleteRoot();

    cout << "After deletion: ";
    h.print();

    return 0;
}