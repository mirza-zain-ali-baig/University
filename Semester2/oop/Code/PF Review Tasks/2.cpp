#include <iostream>
using namespace std;
void reverse(int &n){
    // int a = n/100;
    // int c = n%10;
    // int b = (n/10)%10;
    // cout << "A, B and C = " << c  << b << a << endl;

    int remainder =0,reverse = 0;

    while(n!=0){
        remainder = n%10;
        reverse = reverse*10  + remainder;
        n = n/10;
    }
    cout << "Reverse number: " << reverse << endl;
}
int main(){
    int n;
    cout << "Enter a number: ";
    cin >> n;
    reverse(n);
}