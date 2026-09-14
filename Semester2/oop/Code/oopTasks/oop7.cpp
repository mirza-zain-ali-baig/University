// Dynamic Allocation
#include <iostream>
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


int main(){
   // int* ptr = new int(12) , it store only one value
   study* ptrr = new study(12,34,12);
   cout << ptrr->breakfastTime << endl;
   delete ptrr;
}