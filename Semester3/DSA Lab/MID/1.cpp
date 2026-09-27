// 👉 Idea:

// Compare adjacent(means ملحق (attatched) or قریب (near) or متصل (connected)) elements and swap them if they are in the wrong order.
// After each pass, the largest element “bubbles up” to the end.

#include<iostream>
using namespace std;

void bubbleSort(int arr[], int n){
    int swapCount= 0;
    for(int i = 0;i<n-1;i++){
        for(int j = 0;j<n-i-1;j++){
            if(arr[j]>arr[j+1]){
                swap(arr[j],arr[j+1]);
                swapCount++;
            }
        }
    }
    cout << "Swap Count: " << swapCount << endl;
}

int main(){
    int arr[5] = {4,3,1,5,2};
    bubbleSort(arr,5);
    for(int i = 0;i<5;i++){
        cout << arr[i] << " ";
    }
    return 0;
}