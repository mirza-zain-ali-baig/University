#include <iostream>
// Template Functions
using namespace std;

template <typename T>


T getLarger(T a, T b ){
    return (a > b) ? a : b;
}

template <typename T>
T getMax(T a, T b) {
    return (a > b) ? a : b;
}

int main(){
    int a = 2,b =3;
    cout << "Max of " << a << " and " << b << " is " << getMax(a,b) << endl;
}