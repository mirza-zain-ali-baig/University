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

     Student operator + (const Student &s1){
        Student temp;
        temp.marks = this->marks + s1.marks;
        return temp;
     }
     Student operator - (const Student &s1){
        Student temp;
        temp.marks = this->marks - s1.marks;
        return temp;
     }
     Student operator * (const Student &s1){
        Student temp;
        temp.marks = this->marks * s1.marks;
        return temp;
     }
     // postfix

     Student operator ++ (int){
        Student temp = *this;
        this->marks++;
        return temp;
     }
     Student& operator ++ (){
        ++marks;
        return *this;
     }

     friend ostream& operator << (ostream &out, const Student &s1){
        out << "Name: "<< s1.StdName << ", ID: " << s1.id << ", Marks: " << s1.marks << endl;
        return out;
     }

     bool operator == (const Student &s1){
        return marks == s1.marks;
     }
};
int main(){
    Student s1, s2("Ali", 20,20), s4("Ahmed", 2, 1);
    Student s3 = s1 +s2 +s4; //here first it add s1 and s2 object then it will return a nameless obj which will add to obj 4 then it again return a obj will assign to obj3 by default copy constructor
    Student s5 = ++s1 + ++s2; // here first ++s1 and ++s2 works then addition work then it will assign to s5;
    s5.display();
    cout << s5 << endl;
    bool check  = s1 ==s2;
    cout << "s1==s2: " << check << endl;
    return 0;
}