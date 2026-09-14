#include<iostream>
using namespace std;

class Rectangle {
    private:
     double length;
     double width;
    public: 
     Rectangle(): length(0), width(0) {};
     Rectangle(double l, double w): length(l), width(w) {};

     double area() const{
        return length * width;
     }
     void showDetails() const{
        cout << "Length: " << length << ", Width: "<< width << endl;
     }     

     // >= operator overloading
     bool operator>=(const Rectangle &r) const{
        return this->area() >= r.area();
     }
};


int main(){
    Rectangle r1(2,3), r2(3,2);
    if ( r1>= r2 ){
        cout << "R1 is Greater than or equal to R2"<< endl;
    }
    return 0;
}