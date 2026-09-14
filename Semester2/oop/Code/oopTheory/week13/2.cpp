#include <iostream>
using namespace std;

class Base {
public:
    virtual void display() {       // virtual keyword
        cout << "Base Display" << endl;
    }
};

class Derived : public Base {
public:
    void display() override {   
 // overridden function
        cout << "Derived Display" << endl;
    }
};

int main(){
    Derived d;
    d.display();
}