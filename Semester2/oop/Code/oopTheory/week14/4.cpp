#include<iostream>
#include<vector>

// I LOVE YOU VECTORS
using namespace std;

class Student{
    private:
     string name;
     int age;
    public:
        Student(){
            name = "";
            age = 0;
        }
        Student(string sname, int sage): name(sname), age(sage) {
        }

        void display() const{
            cout << "Student Name: " << name << endl;
            cout << "Student Age: " << age << endl;
        }
};

int main(){
    vector<Student> students;
    students.push_back( Student("John", 20) );
    students.push_back( Student("Alice", 22) );
    students.push_back( Student("Bob", 19) );

    for(const auto &student : students){
        student.display();
        cout << "-----------------" << endl;
    }

    return 0;
}