#include <iostream>
using namespace std;

class Room{
    double area;
    int numberOfDoors;
    int numberOfWindows;
    public:
     Room(): area(0), numberOfDoors(0), numberOfWindows(0)   {}
     Room(double a, int d, int w):  area(a), numberOfDoors(d), numberOfWindows(w) {}
     void showRoom(){
        cout << "Area: " << area << " , number of Doors: " << numberOfDoors << " , Number of Windows: " << numberOfWindows << endl;
     }
};

class House{
    Room r1;
    string address;
    public:
     House(){
        address = "Null";
     }
     House(double a, int d,int w, string ad): r1(a,d, w), address(ad) { }
     void showHouse(){
        cout << "Address: " << address  << " ";
        r1.showRoom(); 
     }
};


int main(){
    House h1(1200, 10,40,"Mughal Pura, Lahore");
    h1.showHouse();
    return 0;
}