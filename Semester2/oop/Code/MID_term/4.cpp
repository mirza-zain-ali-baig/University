#include <iostream>
using namespace std;

class Marks{
    private:
     int marks;
    public:
     Marks(): marks(0) {};
     Marks(int m): marks(m) {};
     Marks operator++(int) { // postfix
        Marks temp = *this;   
        this->marks++;
        return temp;     
     }
     Marks& operator++(){
        ++marks;
        return *this;
     }
     void display(){
        cout << "Marks: " << marks << endl;
     }
};


int main(){
    Marks m(1), m1(0);
    m.display();
    m1= m++;
    m1.display();
}