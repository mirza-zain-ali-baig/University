#include <iostream>
using namespace std;

class ClockType{
    private:
     int seconds;
     int minutes;
     int hours;

    public:
     void setSeconds(int s){
        seconds = s;
     }
     void setMinutes(int m){
        minutes = m;
     }
     void setHours(int h){
        hours = h;
     }
     void setTime(int h, int m, int s){
         setHours(h);
         setMinutes(m);
         setSeconds(s);
     }
     void getTime(int &h, int &m,int &s){
        h = hours;
        m = minutes;
        s = seconds;
     }
     void incrementHour(){
        if(hours== 24){
            hours=(hours++)%24;
        }
        else{
            hours++;
        }
     }
     void incrementMinutes(){
        if(minutes== 60){
           minutes = (minutes++)%60;
        }
        else{
            minutes++;
        }
     }
     void incrementSeconds(){
        if(seconds== 60){
            seconds = (++seconds)%60;
        }
        else{
            seconds++;
        }
     }
     void displayTime(){
        cout << "Time: " << hours << ":" << minutes << ":" << seconds << endl;
     }
};


int main(){
    ClockType c1;
    c1.setTime(60,30,2);
    c1.displayTime();
    c1.incrementSeconds();
    c1.displayTime();

    ClockType c2 = c1;
    c2.displayTime();
    return 0;
}