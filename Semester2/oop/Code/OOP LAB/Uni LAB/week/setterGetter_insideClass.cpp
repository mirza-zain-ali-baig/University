#include <iostream>
using namespace std;

class Person{
    private:
     string name;
     int age;
     string phone;
     string cnic;
    public:
     void setName(string n){
        name = n;
     }
     void setAge(int a){
        age = a;
     } 
     void setPhone(string p){
        phone = p;
     }
     void setCNIC(string c){
        cnic = c;
     }
     string getName(){
        return name;
     }
     int getAge(){
        return age;
     }
     string getPhone(){
        return phone;
     }
     string getCnic(){
        return cnic;
     }
     void display(){
 
     }
};

int main(){
  Person p1;
  string name, phone, cnic;
  int age;
  for(int i = 0;i<5;i++){
        cout << "Enter name,age, phone, cnic: ";
        cin >> name >> age >> phone >> cnic;
        p1.setName(name);
        p1.setAge(age);
        p1.setPhone(phone);
        p1.setCNIC(cnic);
        cout << "===========================================" << endl;
        cout << "Your data is: " << endl;
        cout << "Name: " << p1.getName()<< endl;
        cout << "age: " << p1.getAge() << endl;
        cout << "Phone number: " << p1.getPhone() << endl;
        cout << "CNIC: " << p1.getCnic() << endl;
  }
  return 0;
}