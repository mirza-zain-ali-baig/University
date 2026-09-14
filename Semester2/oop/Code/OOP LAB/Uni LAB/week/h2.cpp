#include <iostream>
using namespace std;

class Person{
    private:
     string name;
     int age;
     string phone;
     string cnic;
    public:
     void display(){
        cout << "Enter you name, age, phone, cnic ";
        cin >> name >> age>> phone >> cnic;
        cout << "Your information: ";
        cout << "YOur name: " << name << endl;
        cout << "YOur age: " << age << endl;
        cout << "YOur phone: " << phone << endl;
        cout << "YOur cnic: " << cnic << endl;
     }
};

int main(){
    Person p1, p2,p3,p4,p5 ;
    p1.display();                                      
    p2.display();
    p3.display();
    p4.display();
    p5.display();
    return 0;
}