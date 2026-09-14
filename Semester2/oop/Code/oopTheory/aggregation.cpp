#include<iostream>
using namespace std;
class Student{
    int id;
    public:
        Student(){
            id = 0;
        }
};
class Teacher{
    Student* std;
    public:
     Teacher(Student *t){
        std = t;
     }
};
int main(){
    Student *std;
}