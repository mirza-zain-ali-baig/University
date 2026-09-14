#include <iostream>
using namespace std;

void pointers(){
    int a = 10;
    int*b = &a;
    cout << "B Address: " << b << endl;
    cout << "Printing value using pointer: " << *b << endl;
    // changning vlaue using pointer
    
    *b = 20;
    cout << "after changing value using pointer: " << *b << endl;

}

void pointers(int *a){
    cout << *a << endl;
}

int main(){
    pointers();
    int a = 12;
    int *b = &a;
    pointers(b);
    return 0;
}