#include <iostream>
using namespace std;

class Student{
    private: 
     int id;
     int marks;
    public:
     Student(): id(0), marks(0) {};
     Student(int i, int m): id(i), marks(m) {};

     Student operator+(const Student &s){
        Student temp;
        temp.marks = this->marks + s.marks;
        return temp;
     }

     Student operator- (const Student &s){
        Student temp;
        temp.marks = this->marks - s.marks;
        return temp;
     }
     Student operator/ (const Student &s){
        Student temp;
        temp.marks = this->marks / s.marks;
        return temp;
     }

     Student& operator= (const Student &s){
        this->id = s.id;
        this->marks = s.marks;
        return *this;
     }

     void showDetails(){
        cout << "ID: " << id << ", Marks= "<< marks << endl;
     }
};

 
int main(){
    Student s1(1, 12), s2(2, 13);
    Student s3 = s1+s2;
    s3.showDetails();
    return 0;
}