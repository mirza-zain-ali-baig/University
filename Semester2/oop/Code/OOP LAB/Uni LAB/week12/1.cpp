#include <iostream>
using namespace std;
class Person{
    string name;
    int age;
    public:
     Person(){

     }
     Person(string n, int a){
        name = n;
        age = a;
     }
     string getName() const{
        return name;
     }
     int getAge() const{
        return age;
     }
     void showInfo(){
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
     }
};


class Course {
    string courseName;
    public: 
     Course (){
        courseName = "Null";
     }
     Course(string c){
        courseName = c;
     }
     string getCourseName(){
        return courseName;
     }
};

class Department{
    string deptName;
    public:
     Department(string n){
        deptName = n;
     }

     string getDeptName() const {
        return deptName;
     }
};

class Student: public Person{
    string rollNo;
    Course course;
    public:
     Student(string na, int ag, string r, Course c): Person(na,ag), rollNo(r), course(c) {}
     void showStudent(){
         showInfo();
        cout << "RollNo: " << rollNo << " Course: " << course.getCourseName() << endl;
     }
};


class Teacher: public Person{
    string subject;
    Department dept;
    public: 
     Teacher (string n, int a,string s, Department d): Person(n,a),subject(s),dept(d){ };
     void showTeacher(){
        showInfo();
        cout << "Subject: " << subject << "Department: " << dept.getDeptName() << endl;
     }
};

int main(){
    Course c("OOP");
    Student s1("Ali", 19, "20", c);
    s1.showStudent();

}