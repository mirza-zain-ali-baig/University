#include<iostream>
using namespace std;

class Time{
    private:
     int hours;
     int minutes;
     int seconds;
    public:
     // Default Constructor

     Time(){
        hours = 0;
        minutes = 0;
        seconds = 0;
     }

     // Parmeterised Constructor
     Time(int h,int m,int s){
        hours = h;
        minutes = m;
        seconds = s;
     }


    //  void setHours(int h){
    //     hours = h;
    //  }
    //  void setMinutes(int m ){
    //     minutes = m;
    //  }
    //  void setSeconds(int s){
    //     seconds = s;
    //  }

    //  int getHours(){
    //     return hours;
    //  }
    //  int getMinutes(){
    //     return minutes;
    //  }
    //  int getSeconds(){
    //     return seconds;
    //  }

    //  void setTime(int h, int m, int s){
    //     setHours(h);
    //     setMinutes(m);
    //     setSeconds(s);
    //  }

    //  Time(int h, int m, int s){
    //     setTime(h,m,s);
    //  }

     void display(){
        cout << "Time: " << hours << ":" << minutes << ":" << seconds << endl;
     }
};

int main(){
    Time t1(12,30,12);
    Time t2;
    t1.display();
    t2.display();
    return 0;
}