#include<iostream>
using namespace std;
class Vehicle{
    private:
     
    public:
     Vehicle(){
        cout << "Vehicle Constructor. "<< endl;
     }

     ~Vehicle(){
        cout << "Vehicle Destructor. "<< endl;
     }
};
// Derived Classes

class Car: public Vehicle{
    public:
     Car(){
        cout << "Car Constructor. " << endl;
     }
     ~Car(){
        cout << "Car Destructor. " << endl;
     }
};

class Bicycle: public Vehicle{
    public:
     Bicycle(){
        cout << "Bicycle Constructor. " << endl;
     }
     ~Bicycle(){
        cout << "Bicycle Destructor." << endl;
     }
};
int main(){
    cout << "Creating Car Object. ";
    Car c1;
    cout << "\n \n Ended \n \n ";
    cout << "Crating Bicycle Obj: "<< endl;
    Bicycle b1;
    cout << "ok";
    cout<< "Des: ";
    return 0;
}