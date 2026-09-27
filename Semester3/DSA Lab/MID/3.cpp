// Selection
#include<iostream>
using namespace std;
void SelectionSort(int arr[], int n){
    for(int i = 0;i<n-1;i++){
        int least = i;
        for(int j = i+1;j<n;j++){
            if(arr[least]>arr[j]){
                least = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[least];
        arr[least] = arr[i];

    }
}

