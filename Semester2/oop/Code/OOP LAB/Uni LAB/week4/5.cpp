#include<iostream>
using namespace std;
class Box{
    private:
     double height;
     double length;
     double breadth;
    public:
     Box(){
      height = 0;
      length = 0;
      breadth = 0;
     }
     Box(double h,double l,double b){
      height = h;
      length = l;
      breadth = b;
     }
   //   void setHeight(double h){
   //      height = h;
   //   }
   //   void setLength(double l){
   //      length = l;
   //   }
   //   void setBreadth(double b){
   //      breadth = b;
   //   }
   //   double getHeight(){
   //      return height;
   //   }
   //   double getLength(){
   //      return length;
   //   }
   //   double getBreadth(){
   //      return breadth;
   //   }
     double volume(){
        return height * length * breadth;
     }
};
int main(){
   //  Box b1,b2;
    double h,l,b;
    cout << "Enter height, length and breadth of box 1: ";
    cin >> h >> l >> b;
    Box b1(h,l,b);
    cout << "Volume: " << b1.volume() << endl;
   //  b1.setHeight(h);
   //  b1.setLength(l);
   //  b1.setBreadth(b);
   //  cout << "Volume of Box 1: " << b1.volume() << endl;
    return 0;
}