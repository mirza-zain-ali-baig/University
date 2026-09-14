#include<iostream>
using namespace std;

class Student{
    protected:
     string name;
     double marks;
    public:
        Student(string sname, double smarks): name(sname), marks(smarks) {
        }
    
        void display() const{
            cout << "Student Name: " << name << endl;
            cout << "Student Marks: " << marks << endl;
        }
        


};

// TEmplate function that print the display of any class
template <typename T>
void showData(const T &c1){
    c1.display();
}
int main(){
    Student s1("John", 85.5);
    Student s2("Alice", 92.0);
    showData(s2);

} 