#include <iostream>
using namespace std;
// sum of two objects and return 

class Sum{
    private:
     int a;
     int b;
    public:
     Sum(){
        a = 0;
        b = 0;
     }
     Sum(int a1, int b1){
        a = a1;
        b = b1;
     }
     Sum sum(Sum obj){
        Sum obj1;
        obj1.a = a + obj.a;
        obj1.b = b + obj.b;
        return obj1;
     }

     void display() const{
            cout << "A: " << a << " " << "B: " << b << endl;
     }


};
int main(){
    Sum s0(2,3);
    Sum s1(2,3);
    Sum s3 = s0.sum(s1);
    s3.display();
    return 0;
}