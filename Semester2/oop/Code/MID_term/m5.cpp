#include<iostream>
using namespace std;

class Student{
    int id;
    string name;
    public:
    Student(){
        id = 0;
        name = "Null";
    }
     Student(int i, string n){
        id = i;
        name = n;
     }
     void display() const {
        cout << "Id and Name: " << id << name << endl;
     }
};
int main(){
    Student *s1 = new Student(1,"Zain");
    Student s2[2] = {Student(20, "k"), Student(1, "o")};
    // s2[0] = Student(20, "Ali");
    s2[1].display();
    s1->display();

    delete[] s1;
    return 0;
}