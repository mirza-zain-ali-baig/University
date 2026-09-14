#include<iostream>
#include<string>
using namespace std;

class Student{
    string name;
    int rollNO;
    double cgpa;
    public:
     Student(){
        name = "NUlL";
        rollNO = 0;
        cgpa = 0;
     }

     Student(string n, int r, int c){
        name = n;
        rollNO = r;
        cgpa = c;
     }

     void input(){
        cout << "Enter the name: ";
        getline(cin, name);
        cout << "Enter the Roll No: ";
        cin >> rollNO;
        cout << "Enter the CGPA: ";
        cin >> cgpa;
     }

     void display() const {
        cout << "NAME: " << name << ", ROLL NO: " << rollNO << ", CGPA: " << cgpa << endl;  
     }
};


int main(){
    Student s1;
    s1.input();
    s1.display();
    Student s2( "ZAin", 20, 3.7 );
    s2.display();
    return 0;
}