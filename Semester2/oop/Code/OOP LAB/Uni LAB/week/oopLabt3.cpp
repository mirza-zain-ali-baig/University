//Task 1: Call by Value, Reference, and Pointer
//  Write three functions incrementByValue(int x),
// incrementByReference(int &x), and incrementByPointer(int *x).
//  Demonstrate the difference in main() by passing the same variable
// and printing results after each call.

#include <iostream>
using namespace std;
int incrementByValue(int x){
    return  ++x;
}
int incrementByReference(int &x){
    return ++x;
}
int incrementByPointer(int *x){
    return ++*x;
}
int main(){
    int x = 12;
    cout <<  incrementByValue(x)<< endl;
    cout << incrementByReference(x) << endl;
    cout << incrementByPointer(&x) << endl;
    cout << x << endl;
    return 0;

}