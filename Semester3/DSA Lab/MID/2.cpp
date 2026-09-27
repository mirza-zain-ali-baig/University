#include<iostream>
using namespace std;
void bubbleSortOptimized(int arr[], int n){
    for(int i = 0;i<n-1;i++){
        bool isSwapped = false;
        for(int  j= 0;j<n-i-1;j++){
            if(arr[j]>arr[j+1]){
                isSwapped = true;
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
        if(!isSwapped){
            cout << "Array is Already Sorted." << endl;
            return;
        }
    }
}
int main(){
    int arr[3] = {2,3,4};
    bubbleSortOptimized(arr,3);
    for(int i = 0;i<3;i++){
        cout << arr[i] << " " ;
    }

}