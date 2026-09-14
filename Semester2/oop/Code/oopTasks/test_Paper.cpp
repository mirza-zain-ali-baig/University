// Write a program that counts multiples of a given number lying between
// two numbers. :

#include <iostream>
using namespace std;
int main(){
    // int number,lower, upper, count = 0;
    // cout << "Enter a number: ";
    // cin >> number;
    // cout << "Enter lower number: ";
    // cin >> lower;
    // cout << "Enter upper number: ";
    // cin >> upper;
    // for ( int i = lower; i <=upper; i++){
    //     if ( i % number == 0){
    //         count++;
    //     }
    // }
    // cout << "Count: " << count << endl;

    int n1, n2;
    cout << "Enter n1 aand n2: ";
    cin >> n1 >> n2;
    for (int i = n1; i<=n2; i++){
        if(i%2 == 0){
            cout << i << endl;
        }
    }
    return 0;
}


