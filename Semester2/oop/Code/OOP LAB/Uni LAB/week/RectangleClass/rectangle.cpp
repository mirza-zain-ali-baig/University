#include "Rectangle.h"
#include<iostream>
using namespace std;

void Rectangle::setLength(double l){
    len=l;
}
void Rectangle::setWidth(double w){
    width = w;
}
double Rectangle::getLength(){
    return len;
}
double Rectangle::getWidth(){
    return width;
}
double Rectangle::getArea(){
    return len*width;
}
