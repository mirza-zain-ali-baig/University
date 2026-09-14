#include <iostream>
using namespace std;
// class Std{
//     int id;
//     string name;
//     public:
//      Std(){
//         id = 0;
//         name = "Null";
//      }
//      friend ostream& operator<< (ostream &cout, const Std &b);
// };



// ostream& operator<< (ostream &cout, const Std &b){
//     cout << "Id: "<< b.id << endl;
//     cout << "name: " << b.name << endl;
//     return cout;
// }


// int main(){
//     Std s1;

//    cout << s1 << endl;
// }


class A{
    float a;
    float b;
    public:
     A(float a1, float b1): a(a1), b(b1){};
     A operator + (const A &obj){
        A temp(0,0);
        temp.a = this->a + obj.a;
        temp.b = this->b + obj.b;
        return temp;
     }

     friend ostream& operator << (ostream &cout, const A obj){
        cout << "a: " << obj.a << endl;
        cout << "b: " << obj.b << endl;
        return cout;
     }
};

int main(){
    A a1(1,2), a2(1,2);
    cout << a1 + a2 << endl;
    return 0;
}