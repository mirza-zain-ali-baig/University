#include <iostream>

#include <cmath> 
using namespace std;

void isArmstrong(int* n ){
    int remainder =0, armstrong = 0;
    
    while(*n!=0){
        remainder = *n%10;
        cout << pow(remainder, 3) << endl;
        armstrong = pow(remainder, 3) + armstrong;
        cout << armstrong << endl;
        *n = *n/10;
    }
    cout << "Armstrong: " << armstrong << " *n = " << *n << endl;
    if(armstrong == *n ){
        cout << "Yes, it is armstrong." << endl;
    }
    else if(armstrong != *n ){
        cout << " It is not armstrong. " << endl;
    }
}

int main(){
    int n;
    cout << "Enter a number: ";
    cin >> n;
    isArmstrong(&n);
}