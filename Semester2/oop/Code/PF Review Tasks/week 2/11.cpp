#include <iostream>
using namespace std;
void bubbleSort(int *arr, int n ){
    for(int i = 0;i<n-1;i++){
        for(int j = 0;j<n-i;j++){
            if( *(arr)> *(arr+1)){
                int temp = *(arr);
                *(arr) = *(arr+1);
                *(arr+1) = temp;
            }
        }
    }

    // Print sorting array

    for(int i = 0; i<n;i++){
        cout << arr[i] << endl;
    }
}
int main(){
    int arr[5] = {20,2,34,19,30};
    int n= sizeof(arr)/sizeof(arr[0]);
    bubbleSort(arr, n);
    return 0;
}