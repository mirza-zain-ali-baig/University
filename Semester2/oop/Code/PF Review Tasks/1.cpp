#include <iostream>
using namespace std;

void isPrime(int n){
    int flag = 1;
    for (int i = 2;i<n;i++){
        if(n%i==0){
            flag = 0;
            break;
        }
    }
    if(flag == 1){
        cout << "Prime"<< endl;

    }
    else {
        cout << "Not prime";
    }
}

int main(){
    int n;
    cout << "Enter a number: ";
    cin >> n;
    isPrime(n);
    return 0;
}