#include <iostream>
using namespace std;
void area(double x){
    cout << x*x << endl;
}
void area(float length, float width){
    cout << length * width << endl;
}

void area( float radius){
    cout << 1/2 * 3.14 * radius* radius << endl;
}

int main(){
    double x;
    float length, width, radius;
    area(radius);
    area(length,width );
    area(radius);
}