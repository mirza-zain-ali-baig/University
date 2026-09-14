#include <iostream>
using namespace std;

class Cir{
    double radius;
    public:
     Cir(){
        radius = 0.0;
     }

     Cir(double r){
        radius = r;
     }
     void setRadius(int r){
        radius = r;
     }

     double getRadius() const{
        return radius;
     }

     double getArea() const {
        return 3.14159 * radius * radius;
     }

};

int main(){
    Cir c1(12), c2(7);
    cout << "C1 Radius: " << c1.getRadius() << endl;
    cout << "C1 ARea: " << c1.getArea() << endl;
    cout << "C2 Radius: " << c2.getRadius() << endl;
    cout << "C2 ARea: " << c2.getArea() << endl;
    return 0;
}
