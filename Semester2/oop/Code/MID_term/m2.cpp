#include <iostream>
using namespace std;

class Point{
    int x;
    int y;
    public:
     Point(){
        x = 0;
        y = 0;
     }

     Point(int a, int b){
        x = a;
        y = b;
     }
     Point(const Point &obj){
        x = obj.x;
        y = obj.y;
     }

     void display() const {
        cout << "X and Y: " << x << " " << y << endl;
     }
};

int main()
{
    Point p1(3,4);
    Point p2 = p1;
    p2.display();
    return 0;
} 
