#include<iostream>
using namespace std;

int count = 0;

int fibonacci(int n){
    if(n == 0){
        return 0;
    }
    if(n == 1){
        return 1;
    }

    if(n ==2){
        count++;
    }

    return fibonacci(n-1) + fibonacci(n-2);
}

int main(){
    int num;
    cout << "Eneter the num: ";
    cin >> num;

    cout << "Fibonaccii: " << fibonacci(num) << endl;

    cout << "Count of f(2): " <<  count << endl;

    return 0;
}