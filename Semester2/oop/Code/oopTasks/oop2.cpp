#include <iostream>
using namespace std;

class Car{ // classs
    public:
    // Attributes
        double speed; 
        string color;
        string name;
        string model;

    // Default (طے شدہ / پہلے سے مقرر) constructor
           Car(){

        }
        Car(double s, string c, string n, string m){ // passing parameter in this
            speed = s;
            color = c;
            name = n;
            model = m;
        }

        // When we write default constructor and constructor with parameters then we can declare like this:
        // Car c1(12.4, "White", "Tyota","C1");
        // And also like this:
        // Car c2;
        // c2.name = "Honda";
};

void print(Car c){
    cout << "Car Name: " << c.name << endl;
    cout << "Car Model: " << c.model << endl;
    cout << "Car Color: " << c.color << endl;
    cout << "Car Speed: " << c.speed << endl;
}

int main(){
    Car c1(12.4, "White", "Tyota","C1");
    print(c1);
    Car c2;
    c2.name = "Honda";
    cout << c2.name << endl;
    return 0;
}