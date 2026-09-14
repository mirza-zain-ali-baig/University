#include<iostream>
using namespace std;

class Animal{
    public:
     virtual void sound(){
        cout << "Animal Sound " << endl; 
     }
};

class Dog: public Animal{
    public:
     void sound() override{
        cout << "Dog barks" << endl;
     }
};

class Cat: public Animal{
    public:
     void sound() override{
        cout << "Cat: Meow " << endl;
     }
};

int main(){
    Cat c1;
    Dog d1;
    c1.sound();
    d1.sound();
    return 0;
}