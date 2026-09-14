#include<iostream>
#include<string>
using namespace std;

class Student{
    int id;
    int marks;
    string name;
    public:
     Student(): id(0), marks(0), name("NULL") {};
     friend ostream& operator<<(ostream &out, const Student &obj){
        out << obj.id << endl;

        out << obj.marks << endl;
        out << obj.name << endl;
        return out;
     }
     friend istream& operator >> (istream &in, Student &obj){
        cout << "Enter the id: ";
        in >> obj.id;
        cout << "Enter the marks: ";
        in >> obj.marks;
        cout << "Enter the name: ";
        in.ignore();
        getline(in,obj.name);
        return in;
     }
};

int main(){
    Student s1;
    cout << s1;
    cin>> s1;
}