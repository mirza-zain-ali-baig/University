#include <iostream>
using namespace std;

class Address{
    string city;
    string street;
    string houseNo;
    public:
     Address(){
        city = "Null";
        street = "null";
        houseNo = "null";
     }
     Address(string c, string s, string h){
        city = c;
        street = s;
        houseNo =h;
     }
     void print() const{
        cout << "Address: "<< city << ", " << street <<", " << houseNo << endl;
     }
};

class Student{
    string name; 
    Address A1; // component object (compositon)
    public:
     Student(): name("null") {};
     Student(string n,const Address &a1){
        name = n;
        A1 = a1;
     }
     void print() const{
        cout << "Name: " << name << endl;
        A1.print();
     }
};

int main(){
    string name = "Mirza Zain";
    Address a1( "Lahore", "GulshanPark 12", "House 22"); 
    Student s1(name, a1); // compound object
    s1.print();
    return 0;
}