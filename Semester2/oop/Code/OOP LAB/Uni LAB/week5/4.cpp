#include <iostream>
using namespace std;
 
class Rectangle{
    double width;
    double height;
    double area;

    public:
     void setDimensions(double h, double w){
        height = h;
        width = w;
     }
     double getArea(){
        area =  width * height;
        return area;
     }
};

int main(){
    Rectangle r1;
    double h,w;
    cout << "Enter height & width: ";
    cin >> h >> w;
    r1.setDimensions(h,w);
    cout << r1.getArea() << endl;
    Rectangle r2 = r1;
    cout << r2.getArea();   
    return 0;     
}