#include <iostream>
using namespace std;

class Car {
private:
    void startEngine() {
        cout << "Engine started." << endl;
    }

public:
    void startCar() {
        startEngine();
        cout << "Car is ready to drive." << endl;
    }
};

int main() {
    Car c;

    c.startCar();

    return 0;
}