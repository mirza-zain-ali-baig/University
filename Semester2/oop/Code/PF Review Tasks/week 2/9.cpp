#include <iostream>
using namespace std;
void findLargest(int arr[], int size);
int main(){
    int size;
    cout << "Enter the size of array: ";
    cin >> size;
    int *arr = new int[size];
    for(int i = 0;i<size;i++){
        cout << "Ente the value: " << i+1 << " ";
        cin >> arr[i];
    }
    findLargest(arr, size);
    return 0;
}

void findLargest(int arr[], int size){
    int *largest = arr;
    for(int *i = arr;arr != 0 ;arr++){
            if(*largest < *i){
                *largest = *i;
            }
    }
    cout << "Largest number: " << *largest << endl; 
}