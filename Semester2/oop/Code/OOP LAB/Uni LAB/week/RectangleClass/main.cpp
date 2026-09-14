
#include "Rectangle.cpp"
#include <iostream>
using namespace std;
int main(){
    Rectangle rec;
    double len, width;
    cout << "Enter len and width: ";
    cin >> len >> width;
    rec.setWidth(width);
    rec.setLength(len);
    cout << rec.getArea() << endl;
    return 0;
}