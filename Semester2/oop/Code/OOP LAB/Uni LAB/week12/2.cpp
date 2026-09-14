#include<iostream>
using namespace std;

class Employee{
    string name;
    int salary;
    public:
     Employee(string n, int s){
        name = n;
        salary = s;
     }

     void showInfo(){
        cout << "Name: " << name << endl;
        cout << "Salary: " << salary << endl;
     }
};

class Manager: private Employee{
    public: 
     Manager(string n, int s): Employee(n, s){};
     void display() {
        showInfo();
     } 
};

int main(){
    Manager m("Mirza Zain", 100000);
    m.display();
    return 0;
}