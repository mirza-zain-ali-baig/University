#include <iostream>
using namespace std;
// int main(){
//     int *p;
//     int a = 12;
//     p = &a;
//     cout << "Address: " <<  p << endl;
//     cout << "Value: " <<  *p << endl;
// }


//2.cpp

int main(){
    char *p;
    char a = 2;
    p = &a;
    cout << "Address: " <<  (void*)p << endl;
    cout << "Value: " << (void*)*p << endl;
}


// 3.cpp
// void sum(int *a, int *b){
//     cout << *a + *b << endl;
// }
// int main(){
//     int a, b;
//     cout << "Enter a and b: ";
//     cin >> a >> b;
//     sum(&a,&b);
//     return 0;
// } 


//4.cpp

// void swap(int *a, int *b){
//     int temp = *a;
//     *a = *b;
//     *b = temp;
//     cout << *a << endl;
//     cout << *b << endl;
// }

// int main(){
//     int a, b;
//     cout << "Enter a: ";
//     cin >> a ;
//     cout << "Enter b: ";
//     cin >> b;
//     swap(&a,&b);
//     return 0;
// }

