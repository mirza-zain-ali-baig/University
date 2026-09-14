#include <iostream>
using namespace std;
int main(){
    int size = 3;
    double sum = 0;
    int arr[size]= {1,3,4};
    int *ptr = arr;
    for(int i= 0;i<size;i++){
        sum += *(ptr+i);
    }

    cout << "Average: " << sum/size;
}