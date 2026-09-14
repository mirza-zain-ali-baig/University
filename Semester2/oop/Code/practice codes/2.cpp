#include <iostream>
using namespace std;

class Instructor{
    private:
     string iName;
     int id;
     string number;
    public:
     Instructor(){
        setter("NUll", 0, "NUll");
     }
     Instructor(string iN, int i, string n){
        setter(iN, i, n);
     }
     void setter(string iN, int i, string n){
        setName(iN);
        id = i;
        number = n;
     }
     void setName(string i){
        iName = i;
     }
};

int main(){
    Instructor i("ali", 30, "90980");
}