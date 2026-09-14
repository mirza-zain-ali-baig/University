#include<iostream>
using namespace std;

class Person{
    protected:
        char a;
        int age;
        string name;
    public:
     Person(){

     }
     Person(int a, string n){
        age = a;
        name = n;
     }
     void print(){
        cout << "Name and Age: " << name << " " << age << endl;
     }
};

class Employee: public Person{
    int id;
    public:
     Employee(int a, string n, int i): Person(a, n), id(i) {};
};
 
int main(){
    Person c;
    return 0;
}