// Bubble Sort

#include<iostream>
using namespace std;

void bubbleSort(int arr[], int n){\
    bool isSwapped = false;
    for(int i = 0;i<n -1;i++){
      for(int j = 0;j<n-i-1;j++){
        if(arr[j]>arr[j+1]){
            swap(arr[j],arr[j+1]);
            isSwapped = true;
            // int temp;
            // arr[j] = arr[j+1];
            // arr[j+1] = temp;
        }
      }
      if(!isSwapped){
        return;
      }
    }
}

void displayArray(int arr[], int n){
    for(int i= 0;i<n;i++){
        cout << arr[i] << " ";
    }
}


int main(){
    int arr[] = {2,1,4,1,5};
    int n = 5;

    bubbleSort(arr,n);
    displayArray(arr,n);

    return 0;
}

// Time complexity, Worst Case: O(n^2) Best Case: Omega(n^2)