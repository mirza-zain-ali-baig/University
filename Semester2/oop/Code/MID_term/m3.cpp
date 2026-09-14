#include <iostream>
using namespace std;

class Test{
    static int a;
    public:
     Test(){
        cout << "Constructor Created. " << endl;
     }
     ~Test(){
        a++;
        cout << "Object deleted. " <<  a << endl;
     }
};

int Test::a =0;

int main(){
    Test t1;
    Test t2,t3,t4;
    
}