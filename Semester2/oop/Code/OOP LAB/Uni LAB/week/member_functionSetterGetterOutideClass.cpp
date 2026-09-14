#include <iostream>
using namespace std;

class Rectangle{
    private:
     // attributes
     double width; // data member 
     double height;
    public:
    // member functions functions inside class
     void setWidth(double);
     void setHeight(double);
     double getWidth() const;
     double getHeight() const;
     double getArea() const;
     // It means this function cannot change any data members of the object.
     // for cleaner code we defined the functions outside the class
     
};

void Rectangle::setWidth(double w){
    width = w;
}

void Rectangle::setHeight(double h){
    height = h;
}

double Rectangle::getHeight() const{
    return height ;
}

double Rectangle::getWidth() const{
    return width;
}

double Rectangle::getArea() const{
    return height * width;
}
int main(){
    Rectangle recBox;
    double width, height;
    cout << "Enter height: ";
    cin >> height;
    cout << "Enter the width: ";
    cin >> width;
    recBox.setHeight(height);
    recBox.setWidth(width);
    recBox.getHeight();
    cout << recBox.getHeight() << endl;
    cout << recBox.getWidth() << endl;
    cout  << "Area: " << recBox.getArea() << endl;
    return 0;
}