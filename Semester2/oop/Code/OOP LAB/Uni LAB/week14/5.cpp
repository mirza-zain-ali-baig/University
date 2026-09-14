#include <iostream>
using namespace std;

class Vehicle{
    public:
     virtual void drive();
};

class Car: public Vehicle{
    public:
    void drive(){
        cout << "Car Drived. ";
    }
};

class  Truck: public Vehicle{
    public:
     void drive(){
        cout << "Truck Drived. ";     }
};

int main(){

}