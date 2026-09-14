//Create a function to calculate the sum of digits of a number using pointers

#include <iostream>
using namespace std;
int  SOD(int *a){
    int remainder =0, sum = 0;
    while(*a!=0){
        remainder = *a % 10;
        sum = sum+remainder;
        *a = *a/10;
    }
    return sum;
}


int main(){
    int n;
    cout << "Enter a number: ";
    cin >> n;
    cout << "SUM: " << SOD(&n);
    
}