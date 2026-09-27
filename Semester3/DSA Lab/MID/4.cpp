#include<iostream>
using namespace std;

void insertionSort(int arr[], int n){
    for(int i = 1,j;i<n;i++){
    cout << "HELLO1" << endl;

        int temp = arr[i];
        for(j = i;j>0 && temp<arr[j-1];j--){
    cout << "HELLO2" << endl;

            arr[j] = arr[j-1];
        }
        arr[j] = temp;
    }
}


int main(){
    cout << "HELLO" << endl;
    int arr[3] = {2,4,1};
    insertionSort(arr,3);
    cout << "ERROR";
    for(int i = 0;i <3;i++){
        cout << arr[i] << " ";
    }
    return 0;
}