// Object Pointers 
// passsing.. in functions


#include<iostream>
using namespace std;

class study{
    public:
     int study_hours;
     int awake;
     int breakfastTime;

     study(int study_hours, int awake, int breakfastTime){
        this->study_hours = study_hours;
        this->awake = awake;
        this->breakfastTime = breakfastTime;
     }
};

void change(study *d){
    d->awake = 12;   // (*d).awake = d->awake
}

int main(){
    study d1(10,9,10);
    study d2(20,7,16);
    change(&d1);
    cout << d1.awake << endl;
    // study* p = &d1;
    // cout << p->awake << endl; // (*p).awake = p->awake
    // (*p).awake = 20;
    // cout << p->awake << endl; // (*p).awake = p->awake

    return 0;
}