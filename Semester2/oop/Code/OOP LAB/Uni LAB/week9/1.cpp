#include<iostream>
using namespace std;

class Employee{
    private:
     string name;
     int id;
     float marks;
    public:
     Employee(string n, int i, float m){
        name = n;
        id = i;
        marks = m;
     }

     void display(){
        cout << "Name: " << name << endl;
        cout << "ID: " << id << endl;
        cout << "MArks: " << marks << endl;
     }
     void ChangeMArks(  float ma){
        marks = ma;
     }

};


int main(){
    Employee *e1 = new Employee("!Zain!", 20, 100);
    e1->ChangeMArks(20);
    e1->display();
    delete e1;
    // after deletion, e1 becomes a dangling pointer (pointer pointing to memory that is no longer valid)
    // we need to make it null
    e1 = nullptr;
}