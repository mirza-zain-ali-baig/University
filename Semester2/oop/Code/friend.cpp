#include<iostream>
using namespace std;
// class Zain{
//     private:
//         int age;
//         unsigned height;
//     public:
//      Zain(){
//         age = 0;
//         height = 0;
//      }
//      friend void name(Zain z1);
// };


// void name(Zain z1){
//     cout << "Height: " << z1.height << endl;
// }

// int main(){
//     Zain z1;
//     name(z1);

//     return 0;
// }


class c1{
    private:
     int age;
     int height;
    public:
     c1(){
        age = 0;
        height = 0;
     }
     friend class c2;
};


class c2{
    private:
     int l1;
    public:
     void print(c1 c){
        cout << "Age: "<< c.age << endl;
     }
};