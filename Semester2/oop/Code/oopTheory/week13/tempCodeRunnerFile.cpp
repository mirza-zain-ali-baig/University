#include<iostream>
using namespace std;
// Derived class Funcions Overloading

class Base{
    int a;
    public:
     Base(){
        a = 0;
     }

     void show(){
        cout << a << endl;
     }
};

class Derived: private Base{
    // overloading
    public:
     void show(int a){
        cout << "A: " << a << endl;
     }
};

int main(){
    Derived d;
    d.show(4); 
}