#include <iostream>
using namespace std;

// Person has a date of Birth

class Date{
   int year;
   int month;
   int day;
   int age;
   public:
    Date(): year(0), month(0), day(0) {}; 
    Date(int y, int m, int d): year(y), month(m) , day(d) {};
    void setDate(int y, int m, int d){
        year = y; month = m; day = d;
    }
    void print() const{
        cout << "DOB:" << year << ", " << month << ", " << day << endl;
    }

    void ages() {
        age = 0;
        for(int i = 0;i<year;i++){
            age++;
        }
    }
    void agePrint() const {
         cout << age << endl;   
    }
};


class Person{
    string Pname;
    Date d;
    public:
     Person(string P, int y, int m, int da){
        Pname = P;
        d.setDate(y,m,da);
     }
     void setPerson(string P,int y, int m, int da){
        Pname = P;
        d.setDate(y,m,da);
        d.ages();
     }

     void print() const{
        cout << "Name: " << Pname << endl;
        d.agePrint();
     } 

};

int main(){

}