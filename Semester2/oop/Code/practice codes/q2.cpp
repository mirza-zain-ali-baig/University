#include<iostream>
#include<cstring>

using namespace std;

class Student{
    char *name;
    public:
     Student(){
        name = nullptr;
     }

     Student(const char *n){
        name = new char[strlen(n)+1];
        strcpy(name, n);
     }

     ~Student(){
        delete[] name;
     }

     Student(const Student &obj){
        this->name = new char[strlen(obj.name)+1];
        strcpy(name, obj.name);
     }

     void setName(const char *a){
        strcpy(name, a);
     }

     void print() const {
        cout << name << endl;
     }
     
};

int main(){
    Student s1("ZAIN");
    s1.print();
    Student s2 = s1;
    s1.setName("ALI");
    s2.print();
    return 0;
}