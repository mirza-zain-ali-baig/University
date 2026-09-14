#include<iostream>
using namespace std;

class Student{
    private: 
     int id;
     string name;
    public:
     Student(): id(0), name("Null") {};
     Student(int i, string n): id(i) , name(n) {};
     void display(){
        cout << "ID: " <<  id << ", Name: " << name << endl;
     }
};

int main(){
    // creating dynamic object 
    Student *s = new Student(2,"Mirza Zain");
    s->display();
    // 2nd way
    (*s).display();
    return 0;
}