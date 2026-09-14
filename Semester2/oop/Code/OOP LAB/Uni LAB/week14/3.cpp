#include<iostream>
using namespace std;

class Animal{
    public:
     virtual void sound(){
        cout << "Animal Sound. "<< endl;
     }

};

class Dog: public Animal{
    void sound(){
        cout << "Dog Barking. " << endl;
    }
};

class Cat: public Animal{
    void sound(){
        cout << "Cat Meowing." << endl;
    }
};


int main(){
    Cat c1;
    Dog d1;
    Animal* animal[5];
    animal[1] = &c1;
    animal[2] = &d1;
    animal[1]->sound();
    animal[2]->sound();

    return 0;
}