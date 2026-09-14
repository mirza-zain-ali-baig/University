#include <iostream>
using namespace std;

class Student{
    public:
      string name;
      int age;
      string religion;
      string classs;
      // constructor overloading
      Student(string n, int a, string r){
        name = n;
        age = a;
        religion = r;
      }
      Student(string n, float a, string r, string c){
        name = n;
        age = a;
        religion = r;
        classs = c;
      }

};
void print(Student c){
    cout << "Name: " << c.name << endl;
    cout << "Age: " << c.age << endl;
    cout << "Religion: " << c.religion << endl;
    cout << "Class: " << c.classs << endl;
}
int main(){
    Student s1("aziz", 12, "Islam", "12h");
    Student s2("aziz", 12, "Christian", "11th");
    Student s3(s1); // Copy Constructor

    s1 = s2; // deep copy
    s1.name = "ali";
    print(s1);
    print(s3);
}