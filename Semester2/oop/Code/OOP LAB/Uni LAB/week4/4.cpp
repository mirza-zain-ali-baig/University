#include<iostream>
using namespace std;
class Student{
    string name;
    string regNumber;
    int cgpa;
    public:
     // Default Constructor
     Student(){
        name = "Null";
        regNumber = "Null";
        cgpa = 0;
     }
     Student(string n,string r,int c){
        name = n;
        regNumber = r;
        cgpa = c;
     }


    //  void setName(string n){
    //     name = n;
    //  }
    //  void setRegNumber(string r){
    //     regNumber = r;
    //  }
    //  void setCgpa(int c){
    //     cgpa = c;
    //  }
    // string getName(){
    //     return name;
    // }
    // string getRegNumber(){
    //     return regNumber;
    // }
    // int getCgpa(){
    //     return cgpa;
    // }
    void display(){
        cout << "Name: " << name << endl;
        cout << "RegNumber: " << regNumber << endl;
        cout << "CGPA: " << cgpa << endl;
    }
};
int main(){
    string name,regNumber;
    int cgpa;
    Student s[5];
    for(int i = 0;i<5;i++){
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter regNumber:";
        cin >> regNumber;
        cout << "Enter cgpa:";
        cin >> cgpa;
        s[i] = Student(name,regNumber,cgpa);
        cout << "         Details are:                   " ;
        s[i].display();
    }
    // for(int i = 0;i<5;i++){
    //     cout << "Enter Name: ";
    //     cin >> name;
    //     s[i].setName(name);
    //     cout << "Enter RegNumber: ";
    //     cin >> regNumber;
    //     s[i].setRegNumber(regNumber);
    //     cout << "Enter CGPA: ";
    //     cin >> cgpa;
    //     s[i].setCgpa(cgpa);
    //     cout << "------------------" << endl;
    //     cout << "Details of Student " << i+1 << endl;
    //     s[i].display();
    // }
    return 0;
}