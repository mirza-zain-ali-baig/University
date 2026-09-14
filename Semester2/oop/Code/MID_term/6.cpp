#include<iostream>
using namespace std;

class Student{
    int id;
    static int count;
    public:
     Student(): id(0) { 
        count++;
     };
     Student(int i): id(i) {
        count++;
     };
     static void CountFunction(){
        cout << count << endl;
     }
};

int Student::count = 0;

int main(){
    Student s1(0),s2;
    Student::CountFunction();
    return 0;
}