// Selection sort:
// 👉 Idea:
// Repeatedly select the smallest element from the unsorted part and place it at the beginning.

#include <iostream>
using namespace std;

void selectionSort(int arr[],int n){
    for(int i= 0;i<n -1;i++){
        int least = i;
        for(int j = i+1;j <n;j++){
            if(arr[least]>arr[j]){
                least = j; // update index of smallest element
            }
        }
        int temp = arr[i];
        arr[i] = arr[least];
        arr[least] = temp;
    }
}



int main(){
    int arr[] = {0,9,4,3,1};
    int n = 5;
    selectionSort(arr,n);
    for(int i = 0;i<n;i++){
        cout << arr[i] << " " ;
    }
    return 0;
}

// Time Complexity in Worst Case: O(n^2)