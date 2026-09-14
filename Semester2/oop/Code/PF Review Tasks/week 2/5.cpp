#include <iostream>
using namespace std;
int main(){
    int arr[5] = {2,4,5,3,6};
    int size = sizeof(arr)/sizeof(arr[0]);
    cout << size << endl;
    int *arrpointer = &arr[4];
    cout << *arrpointer << endl;
    for(int i = 1;i<size;i++){
        cout << *(--arrpointer) << endl;
    }
    return 0;
 }