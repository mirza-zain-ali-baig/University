#include <iostream>
using namespace std;

// class Student{
//     int id;
//     string name;
//     public:
//      Student(){
//         id = 0;
//         name = "Null";
//      }
//      Student(int i, string n){
//         id = i;
//         name = n;
//      }
//      void display(){
//         cout << "NAme and ID:: "<< name << id << endl;
//      }
// };

// class Department{
//     string deptName;
//     string courseName;
//     public:
//      Department(){
//         deptName = "Null";
//         courseName = "null";
//      }
//      Department(string d, string c){
//         deptName = d;
//         courseName = c;
//      }
//      void display(){
//         cout << "DeptNAme: " << deptName << endl;
//         cout << "COurse Name: "  << courseName << endl;
//      }
// };

// class UNiversity{
//     public:
//         Student std1;
//         Department d1;
//         UNiversity(){                      // constructor calls are allowed
//             std1.display();
//             d1.display();
//         }    
// };


// int main(){
//     Student std1;
//     std1.display();
// }



#include <iostream>
using namespace std;

class Engine {
public:
    Engine() {
        cout << "Engine created\n";
    }
    void start() {
        cout << "Engine starting...\n";
    }
};

class Car {
private:
    Engine eng;  // Composition: Car HAS- A Engine;
public:

    Car() {
        cout << "Car created\n";
    }
    void drive() {
        eng.start();
        cout << "Car is moving...\n";
    }
};
class A{
    Car c;
};

int main() {
    Car c;      // Engine automatically created
    c.drive();  // Using Engine through Car
}


