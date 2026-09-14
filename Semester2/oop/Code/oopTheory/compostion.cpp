#include <iostream>
using namespace std;
class Engine{
    int id;
    public:
     Engine(){
        id = 0;
     }
     void setID(int i){
        id = i;
     }
};
class Car{
    string model;
    int id;
    Engine e;
    public:
     Car(){
        model = "Null";
        id = 0;
     }
     Car(string m, int i){
        e.setID(1);
        model = m;
        id = i;
     }
};

int main(){
    Car c;
    return 0;
}