#include<iostream>
#include<cstring>
using namespace std;

class Student{
    char *name; 
    public:
     Student(): name(nullptr) {
        name = new char[1];
        name[0] = '\0';
     };
     Student(const char *n) { name = new char[strlen(n)+1]; strcpy(name, n); }

     ~Student(){
        delete[] name;
     }
     void setName(const char *n){
        strcpy(name, n);
     }

     void print() const{
        cout << name << endl;
     }
};

int main(){
    Student s1("HELLO");
    s1.print();
    Student s2 = s1;
    s1.setName("ALI");
    s2.print();
    return 0;
}

// int main(){
//     const char *name = "ZAIN";
//     cout << name << endl;
//     const char *a = "Ali";
//     name = a;
//     cout << name << endl;
// }