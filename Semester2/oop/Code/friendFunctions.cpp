#include <iostream>
using namespace std;

class Std{
    private:
     int id ;
     string name;
    public:
     Std(int i, string n): id(i) , name(n) {};
     friend void display(const Std &obj);
     
};

void display(const Std &obj){
    cout << obj.id << endl;
    cout << obj.name << endl;
}

int main(){
    Std a(0,"Zain");
    display(a);
    return 0;
}