#include <iostream>
using namespace std;
int  main(){
    int a = 2;
    int *b = &a;
    int **c = &b;
    cout << "Address of pointer to pointer: " << c << endl;
    cout << " And Value: " << **c << endl;

}