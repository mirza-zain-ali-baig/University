#include <iostream>
using namespace std;

class Student{
    private:
     string StdName;
     int id;
     float marks;

    public:
     Student(){
        StdName = "Null";
        id = 0;
        marks = 0;
     }
     Student(string st, int i, float m): StdName(st), id(i) , marks(m) {};
     void display(){
        cout << "STd NAme: " << StdName << endl;
        cout << "STd ID: " << id << endl;
        cout << "Marks: "<< marks << endl;
     }

     friend Student operator + (const Student &s, const Student &s2);
     friend Student operator - (const Student &s, const Student &s2);
     friend Student operator * (const Student &s, const Student &s2);
};

Student operator + (const Student &s, const Student &s2) {
        Student temp;
        temp.marks = s.marks + s2.marks;
        return temp;
}
Student operator * (const Student &s, const Student &s2) {
        Student temp;
        temp.marks = s.marks*s2.marks;
        return temp;
}
Student operator - (const Student &s, const Student &s2) {
        Student temp;
        temp.marks = s.marks - s2.marks;
        return temp;
}



int main(){
    Student s1, s2;
    Student s3= s1 +s2;
    cout << "MArks after addition: " << endl;
    s3.display();
}