#include <iostream>
using namespace std;
void arrayInitialize(int a[]){
    int array[2];
    array[0] = a[0];
    cout << array[0];
}
int main(){
    int array[2];
    array[0]= 1;
    arrayInitialize(array);
    return 0;
}