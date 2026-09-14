#include<iostream>
#include<cstring>
using namespace std;

class Employee{
    char* Name;
    int EmployeeCode;
    double Salary;    
    public:
     Employee(const char* n, int empC, double sal){
        Name = new char[strlen(n)+1];
        strcpy(Name, n);
        EmployeeCode = empC;
        Salary = sal;
     }

     Employee& operator =(const Employee &other){
        Name = new char[strlen(other.Name)+1];
        strcpy(Name, other.Name);
        this->EmployeeCode = other.EmployeeCode;
        this->Salary = other.Salary;
        return *this;
     }
     void display(){
        cout << "Name: " << Name << endl;
        cout << "Employee Code: "  << EmployeeCode << endl;
        cout << "Employee Salary: " << Salary << endl;
     }
     ~Employee(){
        delete[] Name;
     }
};

class Manager: public Employee{
    int workHours;
    double SalaryIncrement;
    public:
     Manager(const char* n, int empC, double Sal, int WorkH, double SI): Employee(n,empC,Sal){
        workHours = WorkH;
        SalaryIncrement = SI;
     }

     Manager& operator = (const Manager &obj){
        Employee::operator=(obj);
        this->workHours = obj.workHours;
        this->SalaryIncrement = obj.SalaryIncrement;
        return *this;
     }

     void display(){
        Employee::display();
        cout << "Work Hours: " << workHours << endl;
        cout << "Salary increment: " << SalaryIncrement << endl;
     }
};