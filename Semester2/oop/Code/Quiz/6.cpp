#include <iostream>
using namespace std;


class Manage{
    private:
     float *arr;
     int size;

    public:
     Manage(int size){
        arr = new float[size];
        for(int i = 0;i<size;i++){
            arr[i] = i+1;
        }
     }
     ~Manage(){
        delete[] arr;
     }

     void storeNumber(int index,int value){
        arr[index] = value;
     }
     float retrieveNumber(int index) const{
        return arr[index];
     }
     float heighestValue(){
        float max = arr[0];
        for(int i = 0;i<size;i++){
            if(arr[i]>max){
             max = arr[i];
            }

        }
        return max;
     }

     float lowestValue(){
        float min = arr[0];
        for(int i = 0;i<size;i++){
            if(arr[i]<min){
            min = arr[i];
            }
        }
        return min;

     }

     float average(){
        float sum = 0;
        float average;
        for(int i = 0;i<size;i++){
            sum = sum+arr[i];
        }
        average = sum/size;
        return average;

     }
};

int main(){
    Manage m(2);
    cout << m.retrieveNumber(1) << endl;
    cout << m.heighestValue() << endl;

}



// Task 02
// class Time{
//     private:
//      int hours;
//      int minutes;
//      int seconds;

//     public:

//      Time(){
//         hours = 0;
//         minutes = 0;
//         seconds = 0;
//      }

//      void setHours(int h){
//         if(h>=0 && h<24){
//             hours = h;
//         }
//         else{
//             hours = 0;
//         }
//      }
//      void setMinutes(int m){
//         if(m>=0 && m<60){
//             minutes = m;
//         }
//         else{
//             minutes = 0;
//         }
//      }
//      void setSeconds(int s){
//         if(s>0 && s<60){
//             seconds= s;
//         }
//         else{
//             seconds= 0;
//         }
//      }

//      void incrementTime(){
//         seconds++;
//         if(seconds==60){
//             seconds = 59;
//             minutes++;
//             if(minutes==60){
//                 minutes = 59;
//                 hours++;
//             }
//         }
//      }

//      void display() const{
//         cout << hours << ":" << minutes<< ":" <<seconds << endl;
//      }

//      void display12HourFormat(){
//         if(hours>=12){
            
//             cout << hours%12 << ":" << minutes << ":" << seconds  << " PM" << endl;
//         }
//         else{
//         cout << hours << ":" << minutes<< ":" <<seconds << " Am" << endl;
//         }
//      }

//      int getHours() const{
//         return hours;
//      }
//      int getMinutes() const{
//         return minutes;
//      }
//      int getSeconds() const{
//         return seconds;
//      }


//      Time(const Time &obj){
//         hours = obj.hours;
//         minutes = obj.minutes;
//         seconds = obj.seconds;
//      }
// };

// int main(){
//     Time t1;
//     t1.setHours(23);
//     t1.setMinutes(30);
//     t1.setSeconds(30);
//     t1.display();
//     t1.display12HourFormat();
//     Time t2 = t1;

//     t2.display(); 
//     return 0;
// }