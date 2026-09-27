// Insertion Sort

#include<iostream>
using namespace std;

void insertionSort(int arr[],int n){
    for(int i = 1,j;i<n;i++){
        int temp = arr[i];
        for( j = i;j>0 && temp  < arr[j-1];j++){
            arr[j] = arr[j-1];
        }
        arr[j] = temp;
    }
}

int main(){

}