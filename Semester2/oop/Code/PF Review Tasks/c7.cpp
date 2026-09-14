#include <iostream>
using namespace std;

void area(double radius){
    cout << " Area of a circle is: " <<  3.14 * radius * radius << endl;
}
void area(double length, double width){
    cout << "Area of Rectangle: " << length * width << endl;
}

int main(){
    float radius,length, width;
    cout << "Enter radius: ";
    cin >> radius;
    cout << "Enter length and width: ";
    cin >> length >> width;
    area(radius);
    area(length, width);
    return 0;
}