#include<iostream>
using namespace std;

class Change{
    public:
     virtual void gearChnage()=0;
};


class Hello{
    private:
     string name;
     string message;

    public:
     Hello(){
        name = "";
        message = "";
     }
     Hello(string n, string m){
        name = n;
        message = m;
     }

     Hello( Hello &h1){
        this->name = h1.name;
        this->message= h1.message;
     }


     void print(){
            cout << "Name: " << name << "Message " << message << endl;
     }

};


template <typename T>

T sum(T a, T b){
    return a+b;
}



int main(){
    Hello h1;
    Hello h2("Ali", "hi");
    h1 = h2;
    cout << sum(2,2) << endl;
    struct hello{
        string name;
        string message;

        void print(){
            cout << "Name: " << name << "Message " << message << endl;
        }
    };
    return 0;
}
